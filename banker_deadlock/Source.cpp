#include<iostream>
#include<vector>
#include<string>
#include <fstream>
using namespace std;

//xay dung ham kiem tra chuoi trang thai co an toan khong
vector<int> SaftyAlgorithm(vector<vector<int>> need, vector<vector<int>> alloc, vector<int> available, int n, int m) {
	vector<int> work(m);
	vector<bool> finish(n, false);
	bool flag = true;
	vector<int>safe_state;
	for (int i = 0; i < m; i++) { work[i] = available[i]; }
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++) {
			if (finish[i] == false) {
				flag = true;
				for (int j = 0; j < m; j++) {
					if (need[i][j] > work[j]) {
						flag = false;
					}
				}
				if (flag) {
					for (int j = 0; j < m; j++) {
						work[j] = work[j] + alloc[i][j];
					}
					finish[i] = true;
					safe_state.push_back(i);
				}

			}

		}

	for (int i = 0; i < n; i++) {
		if (finish[i] == false) {
			vector<int> v(n + 1);
			return v;
		}
	}
	safe_state.push_back(1);
	return safe_state;
}

//ham thuc hien thay moi, kiem tra gia tri moi xem co dap ung duoc khong
vector<int> ResourceRequestAlgorithm(vector<vector<int> >& need, vector<vector<int> >& alloc, vector<int>& available, vector<int>request, int proccess, int n, int m) {
	bool flag = true;
	vector<int>safe_state;
	for (int j = 0; j < m; j++) {
		if ((need[proccess][j] < request[j]) || (available[j] < request[j])) {
			flag = false;
		}

	}
	if (flag) {
		for (int i = 0; i < m; i++) {
			available[i] = available[i] - request[i];
			alloc[proccess][i] = alloc[proccess][i] + request[i];
			need[proccess][i] = need[proccess][i] - request[i];
		}
		safe_state = SaftyAlgorithm(need, alloc, available, n, m);
		if (!safe_state[n]) {
			for (int i = 0; i < m; i++) {
				available[i] = available[i] + request[i];
				alloc[proccess][i] = alloc[proccess][i] - request[i];
				need[proccess][i] = need[proccess][i] + request[i];
			}
			vector<int> v(n + 1);
			return v;
		}
		else {
			safe_state.push_back(1);
			return safe_state;

		}
	}
	else {
		vector<int> v(n + 1);
		return v;
	}
}

int main() {
	int n, m;
	cout << "Nhap n(process) and m(tai nguyen) tuong ung (co khoang cach)" << endl;
	cin >> n >> m;
	vector<int> available(m);
	vector<vector<int>> max(n, vector<int>(m));
	vector<vector<int>> alloc(n, vector<int>(m));
	vector<vector<int>> need(n, vector<int>(m));
	cout << "Nhap allocation matrix: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> alloc[i][j];
		}
	}
	cout << endl;

	cout << "Nhap maximum matrix: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> max[i][j];
		}
	}
	cout << endl;

	cout << "Nhap available matrix: " << endl;
	for (int i = 0; i < m; i++) { cin >> available[i]; }

	//chay vong lap tinh ra bang Need
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			need[i][j] = max[i][j] - alloc[i][j];
		}
	}
	cout << endl;

	cout << "Bang Need matrix" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cout << need[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-------------------" << endl;

	vector<int> req(m);
	int num = 1;
	int proccess = n + 10;
	vector<int>ans;
	string s = "";
	cout << "1. KT trang thai co an toan khong?" << endl;
	cout << "2. KT yeu cau them tai nguyen vo tien trinh" << endl;
	while (true) {

		cout << "Chon 1 hoac 2" << endl;
		cin >> num;
		if (num == 1) {
			ans = SaftyAlgorithm(need, alloc, available, n, m);
		}
		else {
			cout << "Nhap Proccess Num" << endl;
			cin >> proccess;
			cout << "Nhap Request" << endl;
			for (int i = 0; i < m; i++) {
				cin >> req[i];
			}
			ans = ResourceRequestAlgorithm(need, alloc, available, req, proccess, n, m);
		}
		cout << "--------KET QUA--------" << endl;
		if (ans[n] == 0) {	//ket qua chay ham tren = 0, trang thai hien tai khong an toan
			cout << "KHONG AN TOAN" << endl;
		}
		else {				//ket qua khac 0, cho ra chuoi trang thai an toan
			s = "AN TOAN ";
			if (num == 2) {
				s += "<P" + to_string(proccess) + "req" + ",";
			}
			else {
				s += "<";
			}
			for (int i = 0; i < n; i++) {
				if (i == (n - 1)) {
					s += "P" + to_string(ans[i]) + ">";
				}
				else {
					s += "P" + to_string(ans[i]) + ",";
				}
			}
			cout << s << endl;
		}
		cout << "-------------------" << endl;
	}
}