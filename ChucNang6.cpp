#include "stdafx.h"
#include "ChucNang6.h"
#include "Function3.h"
#include "ChucNang4,5.h"
#include "Function2.h"
#include "UI.h"
#include <Windows.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#define borrowlist "C:\\LibManagement\\borrowlist.txt"
#define listBook "C:\\LibManagement\\bookList.bin"
#define ListDocGia  "C:\\LibManagement\\readerList.bin"

struct ISBN
{
	char isbn[14];
};

void xoaPhanTu(ISBN *a, int pos, int &n)
{
	for (int i = pos; i < n-1; i++)
	{
		*(a + pos) = *(a + pos + 1);

	}
	n--;
	a = (ISBN*)realloc(a,sizeof(ISBN)*n);
}

int countLine(char *filename)
{
	char ch;
	int line = 0;
	FILE *f = fopen(filename, "r");
	if (f != NULL)
	{
		while (!feof(f))
		{
			ch = fgetc(f);
			if (ch == '\n' || ch == EOF)
			{
				line++;
			}
		}
		fclose(f);
		line--; // Tru 1 dong trong o dau file
		return line;
	}
	return 0;
}

void statisticMenu(int rank, char **currenUser)
{
	system("cls");

	printf("\n\t\t     ����������������������������������������������������������������������ͻ");
	printf("\n\t\t     �                              THONG KE                                �");
	printf("\n\t\t     ����������������������������������������������������������������������͹");
	printf("\n\t\t     �                                  �                                   �");
	printf("\n\t\t     �1 .THONG KE SACH DANG MUON        �2. DANH SACH DOC GIA TRE HAN       �");
	printf("\n\t\t     �                                  �                                   �");
	if (rank != 2)
	{
		printf("\n\t\t     �3. THONG KE SO LUONG SACH         �4. THONG KE SACH THEO THE LOAI     �");
		printf("\n\t\t     �                                  �                                   �");
		printf("\n\t\t     �5. THONG KE SO LUONG DOC GIA      �6. THONG KE DOC GIA THEO GIOI TINH �");
		printf("\n\t\t     �                                  �                                   �");
	}

	printf("\n\t\t     ����������������������������������������������������������������������ͼ\n");
	printf("\t\t      0. Quay lai man hinh chinh \n");
	printf("\n\t\tNHAP CHUC NANG MUON THUC HIEN: ");

	int ch;
	scanf_s("%i", &ch);
	switch (ch)
	{
	case 0:
		system("cls");
		menu(rank, currenUser);
		break;
	case 1:
		thongKeSachDangMuon();
		break;
	case 2:
		thongKeDocGiaTreHan();
		break;
	case 3:
		if (rank == 2)
		{
			printf("Khong co chuc nang nay ! \n");
			break;
		}
		else
		{
			thongKeSach();
			break;
		}
	case 4:
		if (rank == 2)
		{
			printf("Khong co chuc nang nay ! \n");
			break;
		}
		else
		{
			thongKeSachTheoLoai();
			break;
		}
	case 5:
		if (rank == 2)
		{
			printf("Khong co chuc nang nay ! \n");
			break;
		}
		else
		{
			thongKeDocGia();
			break;
		}
	case 6:
		if (rank == 2)
		{
			printf("Khong co chuc nang nay ! \n");
			break;
		}
		else
		{
			thongKeDocGiaTheoGioiTinh();
			break;
		}
	default:
		printf("Khong co chuc nang nay ! \n");
		break;
	}

Select:
	printf("\n\n\t\t\tNHAN ENTER DE TIEP TUC / NHAN ESC DE QUAY LAI MAN HINH CHINH: ");
	char c = _getch();
	if (c == 13)
	{
		system("cls");
		statisticMenu(rank, currenUser);
	}
	if (c == 27)
	{
		system("cls");
		menu(rank, currenUser);
	}
	else
	{
		goto Select;
	}
}

int soNgayMuon(char ngaymuon[])	// Ham kiem tra bi tre han
{
	time_t hientai = time(NULL);
	struct tm date1 ;
	double seconds;
	date1 = *localtime(&hientai);
	date1.tm_mday = ((int)ngaymuon[0] - 48) * 10 + ((int)ngaymuon[1] - 48);	
	date1.tm_mon=(((int)ngaymuon[3] - 48) * 10 + ((int)ngaymuon[4] - 48))-1;	//year since jan
	date1.tm_year = (((int)ngaymuon[6] - 48) * 1000 + ((int)ngaymuon[7] - 48) * 100 + ((int)ngaymuon[8] - 48) * 10 + ((int)ngaymuon[9] - 48))-1900;	//year since 1900
	seconds = difftime(hientai, mktime(&date1));	//Lay thoi gian giua hai thoi diem
	
	return (seconds / 86400);
}


void thongKeSachDangMuon()
{
	printf("\n\n");
	printf("\t\t\t\t\t\tTHONG KE SACH DANG MUON: \n");
	PhieuMuonSach muonsach;
	int n = countLine(borrowlist);
	FILE *f = fopen(borrowlist, "r");
	if (f == NULL)
	{
		printf("\t\t\tKHONG CO SACH NAO DANG DUOC MUON ");
	}
	else
	{
		int temp;
		int total = 0;

		for (int i = 0; i < n; i++)
		{
			fscanf(f, "%s", muonsach.maDocGia);
			fscanf(f, "%s", muonsach.ngayMuon);
			fscanf(f, "%s", muonsach.ngayTraDuKien);
			fscanf(f, "%i", &temp);
			total += temp;
			for (int j = 0; j < temp; j++)
			{
				fscanf(f, "%s", muonsach.ISBN);
			}
		}

		int real_total = total;

		rewind(f);
		ISBN *maSach;
		maSach = (ISBN*)malloc(sizeof(ISBN)*total);
		int k = 0;
		for (int i = 0; i < n; i++)
		{
			fscanf(f, "%s", muonsach.maDocGia);
			fscanf(f, "%s", muonsach.ngayMuon);
			fscanf(f, "%s", muonsach.ngayTraDuKien);
			fscanf(f, "%i", &temp);
			for (int j = 0; j < temp; j++)
			{
				fscanf(f, "%s", (maSach + k)->isbn);
				k++;
			}
		}

		fclose(f);

		int *a = (int*)calloc(total, sizeof(int));
		for (int i = 0; i < total; i++)
		{
			*(a + i) = 1;
		}

		int t = 0;
		for (int i = 0; i < total - 1; i++)
		{
			for (int j = i + 1; j < total; j++)
			{
				if (strcmp((maSach + i)->isbn, (maSach + j)->isbn) == 0)
				{
					*(a + t) = *(a + t) + 1;
					xoaPhanTu(maSach, j, total);
				}
			}
			t++;
		}

		char tenSach[100];



		printf("\t\t���������������������������������������������������������������������������ͻ\n");
		printf("\t\t�                          TONG SO SACH DANG DUOC MUON: %i                  �\n", real_total);
		printf("\t\t���������������������������������������������������������������������������͹\n");
		printf("\t\t�    ISBN      �                 TEN                  �        SO LUONG     �\n");
		printf("\t\t�              �                                      �                     �\n");
		for (int i = 0; i < total; i++)
		{
			printf("\t\t�%i) %-11s", i + 1, (maSach + i)->isbn);
			timSachTheoISBN((maSach + i)->isbn, tenSach);
			printf("�%-37s ", tenSach);
			printf("�           %-10d", *(a + i));
			printf("�\n");
		}
		printf("\t\t�              �                                      �                     �");
		printf("\n\t\t��������������������������������������������������������������������������ͼ\n");
	}
}

void thongKeDocGiaTreHan()
{
	printf("\n\n");
	printf("\t\t\t\t\t\tTHONG KE DANH SACH DOC GIA BI TRE HAN \n");
	int n=countLine(borrowlist);
	int total = 0;
	int temp;
	PhieuMuonSach muonsach;
	FILE *f = fopen(borrowlist, "r");
	if (f == NULL)
	{
		printf("\t\t\tKHONG CO DOC GIA TRE HAN \n");
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			fscanf(f, "%s", muonsach.maDocGia);
			fscanf(f, "%s", muonsach.ngayMuon);
			if (soNgayMuon(muonsach.ngayMuon) > 7)
			{
				total++;
			}
			fscanf(f, "%s", muonsach.ngayTraDuKien);
			fscanf(f, "%i", &temp);
			for (int j = 0; j < temp; j++)
			{
				fscanf(f, "%s", muonsach.ISBN);
			}
		}

		rewind(f);

		PhieuMuonSach *docGiaTreHan;
		docGiaTreHan = (PhieuMuonSach*)malloc(sizeof(PhieuMuonSach)*total);
		int k = 0;
		for (int i = 0; i < n; i++)
		{
			fscanf(f, "%s", muonsach.maDocGia);
			fscanf(f, "%s", muonsach.ngayMuon);
			if (soNgayMuon(muonsach.ngayMuon) > 7)
			{
				strcpy((docGiaTreHan + k)->maDocGia, muonsach.maDocGia);
				strcpy((docGiaTreHan + k)->ngayMuon, muonsach.ngayMuon);
				k++;
			}
			fscanf(f, "%s", muonsach.ngayTraDuKien);
			fscanf(f, "%i", &temp);
			for (int j = 0; j < temp; j++)
			{
				fscanf(f, "%s", muonsach.ISBN);
			}
		}

		fclose(f);
		char tenDG[50];

		printf("\t\t���������������������������������������������������������������������������ͻ\n");
		printf("\t\t�                          TONG SO DOC GIA TRE HAN: %i                       �\n", total);
		printf("\t\t���������������������������������������������������������������������������͹\n");
		printf("\t\t�  MA DOC GIA  �                   TEN                �      SO NGAY TRE    �\n");
		printf("\t\t�              �                                      �                     �\n");
		for (int i = 0; i < total; i++)
		{
			printf("\t\t�%i) %-11s", i + 1, (docGiaTreHan + i)->maDocGia);
			tenDocGiaTheoMaDG((docGiaTreHan + i)->maDocGia, tenDG);
			printf("�               %-23s", tenDG);
			printf("�          %-11d", soNgayMuon((docGiaTreHan + i)->ngayMuon) - 7);
			printf("�\n");
		}
		printf("\t\t�              �                                      �                     �");
		printf("\n\t\t���������������������������������������������������������������������������͹\n");
	}
}

void thongKeSach()
{
	printf("\n\n");
	printf("\t\t\t\t\tTHONG KE SACH TRONG THU VIEN \n\n");
	Book *book;
	int n;
	docDuLieu(book, n);
	int total = 0;
	
	for (int i = 0; i < n; i++)
	{
		total += (book + i)->soLuong;
	}

	printf("\t\t��������������������������������������������������������������������������ͻ\n");
	printf("\t\t�                         TONG SO SACH TRONG THU VIEN: %i                   �\n",total);
	printf("\t\t��������������������������������������������������������������������������͹\n");
	printf("\t\t�                     TEN                      �          SO LUONG         �\n");
	printf("\t\t�                                              �                           �\n");
	for (int i = 0; i < n; i++)
	{
		printf("\t\t�%i) %-43s",i+1,(book+i)->tenSach);
		printf("�            %-15d", (book + i)->soLuong);
		printf("�\n");
	}
	printf("\t\t�                                              �                           �");
	printf("\n\t\t��������������������������������������������������������������������������͹\n");
	
	free(book);
}

void thongKeSachTheoLoai()
{
	printf("\n\n");
	printf("\t\t\t\t\t\tTHONG KE SACH THEO LOAI: \n\n");
	Book *book;
	int n;
	int total = 0;
	char theLoai[20];
	printf("\t\t\tNhap the loai sach can thong ke: ");
	rewind(stdin);
	gets_s(theLoai);
	docDuLieu(book, n);
	for (int i = 0; i < n; i++)
	{
		if (strcmp(_strupr((book+i)->theLoai),_strupr(theLoai))==0)
			total += (book + i)->soLuong;
	}
	printf("\t\t��������������������������������������������������������������������������ͻ\n");
	printf("\t\t�            TONG SO SACH THE LOAI <%s> TRONG THU VIEN: %i          �\n",theLoai, total);
	printf("\t\t��������������������������������������������������������������������������͹\n");
	printf("\t\t�                     TEN                      �          SO LUONG         �\n");
	printf("\t\t�                                              �                           �\n");
	for (int i = 0; i < n; i++)
	{
		if (strcmp(_strupr((book + i)->theLoai), _strupr(theLoai)) == 0)
		{
			printf("\t\t�%i) %-43s", i + 1, (book + i)->tenSach);
			printf("�            %-15d", (book + i)->soLuong);
			printf("�\n");
		}
	}
	printf("\t\t�                                              �                           �");
	printf("\n\t\t��������������������������������������������������������������������������͹\n");

	free(book);
}

void thongKeDocGia()
{
	printf("\n\n");
	printf("\t\t\t\t\t\tTHONG KE DOC GIA\n\n");
	DocGia *reader;
	int n;
	docDuLieu(reader, n);
	printf("\t\t\tTong so doc gia trong thu vien: %i \n", n);
	printf("\n\t\t\t\t\t\t\t\tDANH SACH CAC DOC GIA CO TRONG THU VIEN LA");
	printf("\n������������������������������������������������������������������������������������������������������������������������������������������������������������������������ͻ");
	printf("\n�Ma DG�             Ho Ten           �    CMND    �   Dab    � SEX �           Email                   �            Dia Chi                        �  Lap the �  Het han �");
	printf("\n������������������������������������������������������������������������������������������������������������������������������������������������������������������������͹");
	for (int i = 0; i < n; i++)
	{
		printf("\n�%-5s", reader[i].MaDocGia);
		printf("�%-30s", reader[i].HoTen);
		printf("�%-12s", reader[i].CMND);
		printf("�%2d/%2d/%4d", reader[i].daB.ngay, reader[i].daB.thang, reader[i].daB.nam);
		printf("�%-5s", reader[i].GioiTinh);
		printf("�%-35s", reader[i].Email);
		printf("�%-43s", reader[i].DiaChi);
		printf("�%2d/%2d/%4d", reader[i].ngaylapthe.ngay, reader[i].ngaylapthe.thang, reader[i].ngaylapthe.nam);
		printf("�%2d/%2d/%4d�", reader[i].ngayhethan.ngay, reader[i].ngayhethan.thang, reader[i].ngayhethan.nam);
	}
	printf("\n������������������������������������������������������������������������������������������������������������������������������������������������������������������������ͼ");
	printf("\n\n");
}

void thongKeDocGiaTheoGioiTinh()
{
	printf("\n\n");
	printf("\t\t\t\t\t\tTHONG KE DOC GIA\n\n");
	DocGia *reader;
	int n;
	int total=0;
	char sex[5];
	printf("\t\t\tNhap gioi tinh can thong ke (Nam/Nu): ");
	rewind(stdin);
	gets_s(sex);

	docDuLieu(reader, n);

	for (int i = 0; i < n; i++)
	{
		if (strcmp(_strupr((reader + i)->GioiTinh), _strupr(sex)) == 0)
		{
			total++;
		}
	}

	printf("\t\t\tTong so doc gia trong thu vien: %i \n", total);
	printf("\n\t\t\t\t\t\t\t\tDANH SACH CAC DOC GIA CO TRONG THU VIEN LA");
	printf("\n������������������������������������������������������������������������������������������������������������������������������������������������������������������������ͻ");
	printf("\n�Ma DG�             Ho Ten           �    CMND    �   Dab    � SEX �           Email                   �            Dia Chi                        �  Lap the �  Het han �");
	printf("\n������������������������������������������������������������������������������������������������������������������������������������������������������������������������͹");
	for (int i = 0; i < n; i++)
	{
		if (strcmp(_strupr((reader + i)->GioiTinh), _strupr(sex)) == 0)
		{
			printf("\n�%-5s", reader[i].MaDocGia);
			printf("�%-30s", reader[i].HoTen);
			printf("�%-12s", reader[i].CMND);
			printf("�%2d/%2d/%4d", reader[i].daB.ngay, reader[i].daB.thang, reader[i].daB.nam);
			printf("�%-5s", reader[i].GioiTinh);
			printf("�%-35s", reader[i].Email);
			printf("�%-43s", reader[i].DiaChi);
			printf("�%2d/%2d/%4d", reader[i].ngaylapthe.ngay, reader[i].ngaylapthe.thang, reader[i].ngaylapthe.nam);
			printf("�%2d/%2d/%4d�", reader[i].ngayhethan.ngay, reader[i].ngayhethan.thang, reader[i].ngayhethan.nam);
		}
	}
	printf("\n������������������������������������������������������������������������������������������������������������������������������������������������������������������������ͼ");
	printf("\n\n");
}