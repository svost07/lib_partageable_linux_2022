
#include <iostream>
#include <dlfcn.h>

int main(int argc, char ** argv)
{
	int data1=3;
	int data2=5;

	int valeur;
	int choice = -1;
	
	//Chose the component 
	while (choice != 1 && choice != 2) {
		std::cout << "Which component do you want? Type 1 or 2." << std::endl;
		std::cin >> choice;
	}
	
	//Open the right file
	void* hndl = nullptr; 
	if (choice == 1){
		hndl = dlopen("./libComposant1.so", RTLD_LAZY);
	}else if (choice == 2){
		hndl = dlopen("./libComposant2.so", RTLD_LAZY);
	}
		
	int (*fct) (int, int);
	if (choice == 1) {
		fct = (int (*) (int, int)) dlsym(hndl, "composant1");
	} else if (choice == 2){
		fct = (int (*) (int, int)) dlsym(hndl, "composant2");
	}
	
	//Return error
	if (!fct) {
		std::cerr << "dlsym : " << dlerror() << std::endl;
		exit(EXIT_FAILURE);
	}
	
	//Final print 
	std::cout << "The value is:" << fct(data1, data2) << std::endl;
	
	//Close 
	dlclose(hndl);
	exit(EXIT_SUCCESS);
}
