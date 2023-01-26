#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#define IDPAQUETE 200
#define IDNODO 201
#define IDPAQUETERIA 202


class paquete{
	private:
		int id;
		string origen;
		string destino;
		float peso;
	public:
		void asignar(int ident,string& o,string& d,float p);
		paquete();
		void salvar(fstream& out);
		void cargar(fstream& in);
		int getclsid();
	friend class nodo;
	friend class paqueteria;		
};

void paquete::asignar(int ident,string& o,string& d,float p){
	id=ident;
	origen=o;
	destino=d;
	peso=p;
};

paquete::paquete(){
};

void paquete::salvar(fstream& out){
	out<<getclsid()<<endl;
	out<<id<<endl;
	out<<origen<<endl;
	out<<destino<<endl;
	out<<peso<<endl;
}

void paquete::cargar(fstream& in){
	in>>id;
	in>>origen;
	in>>destino;
	in>>peso;
}

int paquete::getclsid(){
	return IDPAQUETE;
}

class nodo 
{
	private:
		nodo* psig;
		paquete pk;
	public:
		nodo();
		nodo(int ide,string ori,string des,float ps);
		void salvar(fstream& out);
		void cargar(fstream& in);
		int getclsid();
	friend class paqueteria;
};

nodo::nodo(){
};

nodo::nodo(int ide,string ori,string des,float ps){
	pk.asignar(ide,ori,des,ps);
}

void nodo::salvar(fstream& out){
	out<<getclsid()<<endl;
	pk.salvar(out);
}

void nodo::cargar(fstream& in){
	int id;
	in>>id;
	pk.cargar(in);
}

int nodo::getclsid(){
	return IDNODO;
}

class paqueteria{
	private:
		nodo nodoi;
		nodo nodof;
	public:
		paqueteria();
		void insertaralinicio();
		void eliminaralinicio();
		void mostrar();
		///crear paqute con datos ojoooooooooooooo
		void insertar(int ide,string ori,string des,float ps);
		void insertarnodo(nodo* nuevo);
		int size();
		void guardar(fstream& out);
		void recuperar(fstream& in);
		int getclsid();
};

paqueteria::paqueteria(){
	nodoi.psig=&nodof;
	nodof.psig=NULL;
}

void paqueteria::insertaralinicio(){
	nodo* nuevo=new nodo();
	nuevo->psig=nodoi.psig;
	nodoi.psig=nuevo;
}

void paqueteria::eliminaralinicio(){
	if(nodoi.psig==&nodof)
		cout<<"Paqueteria vacia"<<endl;
	else{
		nodo* p=nodoi.psig;
		nodoi.psig=nodoi.psig->psig;
		delete p;
		cout<<"Paquete eliminado"<<endl;
	}
}

void paqueteria::mostrar(){
	nodo* p=nodoi.psig;
	int i=1;
	while(p->psig!=NULL){
		cout<<"Paquete "<<i<<endl;
		cout<<"ID:"<<p->pk.id<<endl;
		cout<<"Origen:"<<p->pk.origen<<endl;
		cout<<"Destino:"<<p->pk.destino<<endl;
		cout<<"Peso:"<<p->pk.peso<<endl<<endl;
		p=p->psig;
		i++;
	}
}

int paqueteria::size(){
	int nodos=0;
	nodo* p=nodoi.psig;
	while(p!=&nodof)
	{
		p=p->psig;
		nodos++;
	}
	return nodos;
}

void paqueteria::guardar(fstream& out){
	out<<getclsid()<<endl;
	out<<size()<<endl;
	int tam=size()-1;
	nodo* p=&nodoi;
	p=nodoi.psig;
	for(int i=0;i<=tam;i++)
	{
		p->salvar(out);
		p=p->psig;
	}
}

void paqueteria::recuperar(fstream& in){
	int tam=0;
	in>>tam;
	for(int i=0;i<tam;i++){
		int CLSID;
		in>>CLSID;
		nodo* p=new nodo();
		insertarnodo(p);
		p->cargar(in);
	}
}

void paqueteria::insertar(int ide,string ori,string des,float ps){
	nodo* nuevo=new nodo(ide,ori,des,ps);
	nuevo->psig=nodoi.psig;
	nodoi.psig=nuevo;
}

void paqueteria::insertarnodo(nodo* nuevo){
	nuevo->psig=nodoi.psig;
	nodoi.psig=nuevo;
}

int paqueteria::getclsid(){
	return IDPAQUETERIA;
}


int menu(){
	int resp;
	do{
		cout<<"     MENU"<<endl;
		cout<<"1.Agregar paquete"<<endl;
		cout<<"2.Eliminar paquete"<<endl;
		cout<<"3.Mostrar"<<endl;
		cout<<"4.Guardar"<<endl;
		cout<<"5.Recuperar"<<endl;
		cout<<"6.salir"<<endl;
		cin>>resp;
	}while(resp!=1 and resp!=2 and resp!=3 and resp!=4 and resp!=5 and resp!=6);
	return resp;
}

int main(){
	int i;
	paqueteria pk1;
	do{
		i=menu();
		switch(i){
			case 1:{
				int id;
				string d,o;
				float p;
				cout<<"digita el id del paquete"<<endl;
				cin>>id;
				cout<<"agrega el destino del paquete"<<endl;
				cin>>d;
				cout<<"agrega el origen del paquete"<<endl;
				cin>>o;
				cout<<"agrega el peso del paquete"<<endl;
				cin>>p;
				pk1.insertar(id,o,d,p);
				cout<<"paquete agregado"<<endl;
				system("PAUSE");
				system("cls");
				break;
			}
			case 2:{
				cout<<"Se eliminara el ultimo paquete agregado..."<<endl;
				pk1.eliminaralinicio();
				system("PAUSE");
				system("cls");
				break;
			}
			case 3:{
				cout<<"Los paquetes son:"<<endl;
				pk1.mostrar();
				system("PAUSE");
				system("cls");
				break;
			}
			case 4:{
				fstream salida("Paqueteria.txt",ios_base::out);
				pk1.guardar(salida);
				salida.close();
				system("PAUSE");
				system("cls");
				break;
			}
			case 5:{
				fstream entrada("Paqueteria.txt",ios_base::in);
				int id;
				entrada>>id;
				pk1.recuperar(entrada);
				entrada.close();
				system("PAUSE");
				system("cls");
				break;
			}
		}
	}while(i!=6);			
	return 0;
}


