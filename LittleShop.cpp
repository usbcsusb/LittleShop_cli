/*
在3月1日前复习C++内容并提交小卖铺管理系统作业。
硬性要求：使用C++语言，需要有顾客类和老板类，用到继承，使用纯虚函数，至少有两个商品，需要有价钱变化，老板进货，顾客买商品，有余额展示功能。
建议：使用windows.h头文件，gotoxy等让程序更加美观。
*/
#include<Windows.h>
#include<iostream>
#include<math.h>
#include<conio.h>
#include <cstdlib>
static int number=0;

void gotoxy(int x, int y)
{
	COORD p;
	p.X = x;
	p.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}
class Human {//派生顾客和老板
public:
	std::string name;
	float Balance;//账户余额
	virtual int DisplayBalance()=0;	//展示账户余额
private:
	
};
class Boss :public Human{//老板能1查询店铺里的所有货品，2能进货，3能查看店铺账户余额，4能查看购购买次数，5能添加新货物
public:
	Boss() { name = "boss"; Balance = 99999; }
	void viewshop();
	void Purchase();
	int DisplayBalance();
	void ViewNum();
	void AddNewGood();
	
};
void Boss::viewshop() {

}
void Boss::Purchase() {

}
int Boss::DisplayBalance() {
	return 0;
}
void Boss::ViewNum() {

}
void Boss::AddNewGood() {

}
class Customer :Human{//顾客能1查询店铺里的所有货品，2购买（购买前自动显示账户余额），3能和售货小妹打招呼
	
public:
	void viewshop();
	void Buy(float money);
	void Hello();
	int DisplayBalance();
	void SetBalance(float num) {
		Balance = num;
	}
	
private :
	float Balance;
};
void Customer ::viewshop(){}
void Customer::Buy(float money){
	Balance -=  money;
}
void Customer::Hello(){}
int Customer::DisplayBalance() { return 0; }
/*class SalesGirl :Human {

};*/
class Good {//多个Good使用链表链接，方便添加以及后续增加新功能
//（名称，余量，价格）
public:
	std::string name;
	int num;
	float price;
	Good* next;
	//Good* pre;
};

class Shop {

public:
	Shop() {
		Balance = 200;
	}
	void SetBalance(float Money){
		Balance += Money;
		}
	void DisplayBalance() {
		std::cout << "    商店账户余额：   " << Balance << std::endl;
	}
	void  ShowAllGood(Good*pgood);//展示商品（名称，数量，余量，价格）
private:
	float Balance;
	  
};
void Shop::ShowAllGood(Good*HeadGood ) {
	Good* pt=HeadGood->next;
	while(pt->next){
		std::cout << pt->name <<"\n余量：" <<pt->num <<"\n价格"<< pt->price << std::endl;
		pt = pt->next;
	}
	std::cout << pt->name << "\n余量：" << pt->num << "\n价格" << pt->price << std::endl;
}

//主菜单
void mainmenu(Customer * pcustomer,Shop *pshop,Boss*pboss,Good*pgood,Good*HeadGood) {
	Good* pt = HeadGood;
	int type;
	std::string choice;
	
	menu:
	system("cls");
	//gotoxy(10, 5);
	
	std::cout << "1.顾客模式\n2.店铺老板\n3.退出\n" << std::endl;

	
	std::cin >> type;
	switch (type) 
	{
	case 1:
	aaa:
		getche();
		system("cls");
		std::cout << "顾 客 模 式\n";
		pcustomer->DisplayBalance();
		std::cout << "请输入          \n看看商店卖些什么：viewshop      \n购买：Buy		\n和售货小哥哥/小姐姐打招呼：Hello\n         返回主菜单：Exit\n";
		std::cin >> choice;
		while (choice != "Buy" && choice != "viewshop" && choice != "Hello"&&choice!="Exit")
		{
			std::cout << "输入错误，请按下回车确认后重新输入\n"; getche();
			std::cin >> choice;
		}
			if (choice == "Buy") {
				std::cout << "要买些什么？\n";
				pshop->ShowAllGood(HeadGood);
				std::cout << "请输入要买的商品名称（区分大小写）\n";
				std::cin >> choice;
				
				
				
				while (pt->name!=choice&&pt->next!=NULL) {
					pt = pt->next;
			
				}
				std::cout << "已经购买" << pt->name <<"  价格为"<<pt->price<< std::endl;
				number++;
				pcustomer->Buy(pt->price);
				pshop->SetBalance(pt -> price);
				pt->num--;
				std::cout << "剩余量" << pt->num << std::endl;
				goto aaa;
			}
			else if (choice == "viewshop") {
				pshop->ShowAllGood(HeadGood);
				goto aaa;
			}
			else if (choice == "Hello") {
				std::cout << "Hello" << std::endl;
				goto aaa;
			}
			else if (choice == "Exit") {
				goto menu;
			}
			
			break;
	case 2: 
	bbb:
		getche();
		system("cls");
		std::cout << "店 铺 老 板" << std::endl;
		pshop->DisplayBalance();
		//老板能1查询店铺里的所有货品，2能进货，3能查看店铺账户余额，4能查看购购买次数，5能添加新货物,
		std::cout << "1查询店铺里的所有货品，2进货，3查看店铺账户余额，4查看购购买次数，5添加新货物,6,修改商品价格7退出\n";
		std::cin >> type;
		switch (type) {
		case 1:pshop->ShowAllGood(HeadGood); break;
		case 2:
			std::cout << "请输入进货的货物名称，如需增加新货物，请选择5\n";
			pshop->ShowAllGood(HeadGood);
			std::cin >> choice;
			while (pt->name != choice && pt->next != NULL) {
				pt = pt->next;
			}
			std::cout << "请输入进货数量，当前余量为：" << pt->num << std::endl;
			int i;
			std::cin >> i; pt->num += i;
			std:: cout<< "进货完成" << std::endl;
			break;
		case 3:pshop->DisplayBalance(); break;
		case 4:std::cout << "购买次数" << number << std::endl; break;
		case 5:
			pt = HeadGood;
			while (pt->next != NULL) {
				pt = pt->next;
			}
			pt->next = new Good;
			pt = pt->next;
			pt->next = NULL; 
			std::cout << "请输入货品名称" << std::endl;
			
			std::cin >> pt->name;
			std::cout << "请输入货品数量" << std::endl;
			std::cin >> pt->num;
				std::cout << "请输入货品价格" << std::endl;
			std:: cin>> pt->price;
			std::cout<< "输入完成，展示货架\n";
			pshop->ShowAllGood(HeadGood);
			std::cout << "展示完成\n";
			goto bbb;
		case 6:	
			pshop->ShowAllGood(HeadGood);
			pt = HeadGood;
			std::cout << "请输入商品名称；\n";
			std::cin >> choice;
			while (pt->name!=choice) {
				pt = pt->next;
			}
			std::cout << "要修改的商品名称为：" << pt->name << std::endl;
			std::cout << "请输入商品价格：当前商品价格为" << pt->price << std::endl;
		std:: cin >> pt->price;
			
		case 7: goto menu;
		}
		getche();
		
		goto bbb;
		
	
	case 3: break;
	}
}
void tips() {
	std::cout << "" << std::endl;
}


int main() {
	//为了可以直接使用，这里先进行初始化
	//记录1 由于之前初始化内容写在主函数外，在函数执行后内存被回收，所以把内容放进主函数。。。。
	
	Good* good = new Good;//头结点
	Good TolyBread;
	Good AoLiGei;
	Good MGpaper;
	Good DeliPencil;
	good->next = &TolyBread, good->name = "NULL";
	TolyBread.name = "TolyBread", TolyBread.num = 20, TolyBread.price = 5.00, TolyBread.next = &AoLiGei;
	AoLiGei.name = "AoLiGei", AoLiGei.num = 10, AoLiGei.price = 12.00, AoLiGei.next = &MGpaper;
	MGpaper.name = "MGpaper", MGpaper.num = 30, MGpaper.price = 20.00, MGpaper.next = &DeliPencil;
	DeliPencil.name = "DeLiPencil", DeliPencil.num = 20, DeliPencil.price = 2.00, DeliPencil.next = NULL;

	Customer customer; customer.SetBalance(200);

	Boss Boss;
	 
	Shop shop;
	//初始化结束
	tips();
	//mainmenu(AddCustomer(),AddShop(),AddBoss(), AddGood());
	mainmenu(&customer, &shop,&Boss, &DeliPencil,good);
	return 0;

}
