#include<iostream>
using namespace std;

class matrix {
public:
	int row;
	int col;
	double** a;
	matrix(){}
	matrix(int ROW, int COL)
	{
		row = ROW; col = COL;
		a = new double* [row];
		for(int i=0;i<row;i++)
		{
			a[i] = new double[col];
		}
		cout << "请输入矩阵" << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				cin >> a[i][j];
			}
		}

	}
};
matrix error;
void showmatrix(matrix m)
{
	for (int i = 0; i < m.row; i++)
	{
		for (int j = 0; j < m.col; j++)
		{
			if (m.a[i][j] !=-0)
			{
				cout << m.a[i][j] << " ";
			}
			else  cout << 0<<" ";
		}
		cout<<endl;
	}
}
void showmenu() 
{
	cout << "                      矩阵计算器                        " << endl;
	cout << "请选择需要进行的操作" << endl;
	cout << "  1.求行列式     2.矩阵相加   3.矩阵相减   4.矩阵相乘    5.矩阵求逆   6.矩阵相除" << endl;
}
double det(matrix m)
{
	int ii;//行数
	int jj;//列数
	int n = m.col;
	int iter = 0;//行变换次数
	double det1 = 1, yin;
	for (ii = 0; ii < n; ii++)
	{
		if(m.a[ii][ii]==0)

			for (jj = ii; jj < n; jj++)
			{
				if (m.a[jj][ii] != 0)
				{
					double temp1;
					for (int i = 0; i < n; i++)
					{
						temp1 = m.a[ii][i];
						m.a[ii][i] = m.a[jj][i];
						m.a[ii][i] = temp1;
					}
					iter++;
				}
		    }
		for (int k = ii + 1; k < n; k++)
		{
			yin = (-1) * m.a[k][ii] / m.a[ii][ii];
			for (int u = 0; u < n; u++)
			{
				m.a[k][u] = m.a[k][u] + m.a[ii][u] * yin;
			}
		}
	}
	for (int ii = 0; ii < n; ii++)
	{
		det1 = det1 * m.a[ii][ii];
	}
	return det1;
}
matrix add(matrix A, matrix B)
{
	if ((A.row != B.row) || (A.col != B.col)) { cout << "好好回去学线代吧！！";  return error; }
	else { 
		matrix C; 
		C.row = A.row; C.col = A.col;
		C.a = new double* [C.row];
		for (int i = 0; i < C.row; i++)
		{
			C.a[i] = new double[C.col];
		}
		for (int i = 0; i < C.row; i++)
		{
			for (int j = 0; j < C.col; j++)
			{
				C.a[i][j] = 0;
			}
		}
		for (int i = 0; i < A.row; i++)
		{
			for (int j = 0; j < A.col; j++)
			{
				C.a[i][j] = A.a[i][j] + B.a[i][j];
			}
		}
		return C;
		delete C.a;
	}
}
matrix mminus(matrix A, matrix B)
{
	if ((A.row != B.row) || (A.col != B.col)) { cout << "好好回去学线代吧！！";  return error; }
	else {
		matrix C;
		C.row = A.row; C.col = A.col;
		for (int i = 0; i < C.row; i++)
		{
			C.a[i] = new double[C.col];
		}
		for (int i = 0; i < C.row; i++)
		{
			for (int j = 0; j < C.col; j++)
			{
				C.a[i][j] = 0;
			}
		}
		for (int i = 0; i < A.row; i++)
		{
			for (int j = 0; j < A.col; j++)
			{
				C.a[i][j] = A.a[i][j] - B.a[i][j];
			}
		}
		return C;
		delete C.a;
	}
}
matrix mmultiple(matrix A, matrix B)
{
	if (A.col != B.row) { cout << "学你马呢，复习去" << endl;  return error; }
	else 
	{
		int c1 = A.row, c2 = B.col;
		matrix c;
		c.col = c2; c.row = c1;
		c.a = new double* [c1];
		for (int i = 0; i < c1; i++)
		{
			c.a[i] = new double[c2];
		}
		for (int i = 0; i < c1; i++)
		{
			for (int j = 0; j <<c2; j++)
			{
				c.a[i][j] = 0;
			}
		}
		int l = A.col;
		for(int i=0;i<c1;i++)
		{
			for (int j = 0; j < c2; j++)
			{
				for (int k = 0; k < l; k++)
				{
					c.a[i][j] += A.a[i][k] * B.a[k][j];
				}
			}
		}
		return c;
		delete c.a;
	}
}
matrix adj(matrix m, int ROW, int COL)
{
	matrix c;
	c.col = m.col - 1; c.row = m.row - 1;
	c.a = new double* [c.row];
	double sign = ((ROW + COL) % 2 == 0 ? 1 : -1);
	for (int z = 0; z < c.row; z++)
	{
		c.a[z] = new double[c.col];
	}
	for (int i = 0; i < c.row; i++)
	{
		for (int j = 0; j < c.col; j++)
		{
			if ((i < ROW) && (j < COL)) { c.a[i][j] = sign*m.a[i][j]; }
			else if ((i < ROW) && (j >=COL)) { c.a[i][j] = sign*m.a[i][j+1]; }
			else if ((i >=ROW) && (j < COL)) { c.a[i][j] = sign*m.a[i+1][j]; }
			else  if ((i >=ROW) && (j>=COL)) { c.a[i][j] = sign*m.a[i+1][j+1]; }
		}
	}
	return c;
	delete c.a;
}
matrix inverse(matrix m)
{
	if (det(m) == 0) {
		cout << "无法求逆"; return error;
	}
	else {
		matrix c;
		c.col = m.col; c.row = m.row;
		c.a = new double* [c.row];
		for (int i = 0; i < c.row; i++)
		{
			c.a[i] = new double[c.col];
		}
		for (int i = 0; i < c.row; i++)
		{
			for (int j = 0; j < c.col; j++)
			{
				
				c.a[i][j] =det(adj(m, j, i)) / det(m);
			}
		}
		return c;
		delete c.a;
	}
	
}
void test01()
{
	matrix m(3, 3);
	showmatrix(inverse(m));
}
int main() 
{
	/*while (1)
	{
		showmenu();
		int  c;
		cin >> c;
		switch (c)
		{
		case 1: 
		{   cout << "请输入矩阵的行数";
		    int n;
			cin >> n;
			matrix m(n,n);
			cout<<det(m);
			delete m.a;
			break; 
		}
		case 2: 
		{
			cout << "请输入矩阵的行和列:" << endl;
			int l1, l2;
			cin >> l1 >> l2;
			cout << "请输入矩阵A";
			matrix A(l1, l2);
			cout << "请输入矩阵B";
			matrix B(l1, l2);
			showmatrix(add(A, B));
			delete A.a;
			delete B.a;
			break;
		}
		case 3: {
			cout << "请输入矩阵的行和列:" << endl;
			int l1, l2;
			cin >> l1 >> l2;
			cout << "请输入矩阵A";
			matrix A(l1, l2);
			cout << "请输入矩阵B";
			matrix B(l1, l2);
			showmatrix(mminus(A,B));
			delete A.a;
			delete B.a;
			break;
		}
		case 4:
		{
			cout << "请输入矩阵A的行和列:" << endl;
			int l1, l2;
			cin >> l1 >> l2;
			cout << "请输入矩阵A";
			matrix A(l1, l2);
			cout << "请输入矩阵B的行和列:" << endl;
			int l3, l4;
			cin >> l3 >> l4;
			cout << "请输入矩阵B";
			matrix B(l3, l4);
			showmatrix(mmultiple(A, B));
			delete A.a;
			delete B.a;
			break;
		}
		case 5: 
		{  
			cout << "请输入矩阵的行数";
		int n;
		cin >> n;
		matrix m(n, n);
		showmatrix(inverse(m));
		break; 
		}
		case 6: 
		{
			cout << "请输入被除矩阵A的行和列:" << endl;
			int l1, l2;
			cin >> l1 >> l2;
			cout << "请输入矩阵A";
			matrix A(l1, l2);
			cout << "请输入除数矩阵B的行和列:" << endl;
			int l;
			cin >> l;
			cout << "请输入矩阵B";
			matrix B(l, l);
			showmatrix(mmultiple(A, inverse(B)));
			delete A.a;
			delete B.a;
			break;
		}
		}
	}*/
	 test01();
	return 0;
}
