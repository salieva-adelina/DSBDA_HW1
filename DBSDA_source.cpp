// DBSDA_source.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>

using namespace std;

struct Matrix {
	int width;
	int height;
	int** items;
};

Matrix read(ifstream& file) {
	Matrix M;
	M.width = M.height = 0;
	file >> M.width >> M.height;
	if (M.width == 0 || M.height == 0) {
		M.items = nullptr;
		return M;
	}

	M.items = new int* [M.height];
	for (int i = 0; i < M.height; ++i)
		M.items[i] = new int[M.width];
	for (int i = 0; i < M.height; ++i)
		for (int j = 0; j < M.width; ++j)
			file >> M.items[i][j];
	return M;
}

Matrix make(const Matrix& M) {
	Matrix N;
	N.width = M.width;
	N.height = M.height;
	N.items = new int* [N.height];
	for (int i = 0; i < N.height; ++i)
		N.items[i] = new int[N.width];
	for (int i = 0; i < M.height; ++i) {
		int count = 0;
		//подсчет кол-во чисел > 0
		for (int j = 0; j < M.width; ++j)
			if (M.items[i][j] > 0)
				++count;
		int j = 0;
		//сдвиг влево на count элементов
		for (; j < M.width - count; ++j)
			N.items[i][j] = M.items[i][j + count];
		//дополнение нулями справа
		for (; j < M.width; ++j)
			N.items[i][j] = 0;
	}
	return N;
}

void print(const Matrix& N, ostream& o) {
	o << setw(4) << N.width << setw(4) << N.height << endl;
	for (int i = 0; i < N.height; ++i) {
		for (int j = 0; j < N.width; ++j)
			o << setw(4) << N.items[i][j];
		o << endl;
	}
}

void remove(Matrix& M) {
	for (int i = 0; i < M.height; ++i)
		delete[] M.items[i];
	delete[] M.items;
}

int main() {
	ifstream inputfile;
	ofstream outputfile;
	do {
		cout << "Vvedite imya fayla chtenia: ";
		string fileName;
		cin >> fileName;
		inputfile = ifstream(fileName);
		cout << "Vvedite imya fayla zapisi: ";
		cin >> fileName;
		outputfile = ofstream(fileName);
	} while (!inputfile.is_open() || !outputfile.is_open());

	int time = clock();
	while (!inputfile.eof()) {
		Matrix M = read(inputfile);
		if (M.items == nullptr)
			break;
		cout << "Matrica prochitana" << endl;
		//print(M, cout);
		Matrix N = make(M);
		cout << "Matrica sdelana" << endl;
		//print(N, cout);
		print(N, outputfile);
		cout << "Matrica sohranena" << endl;
		remove(M);
		remove(N);
	}
	cout << "time = " << (clock() - time) << " millisecund" << endl;
	outputfile.close();
	inputfile.close();
	return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
