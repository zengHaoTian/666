#include "stdio.h"
#include "malloc.h"
#include "assert.h"
#include "string.h"
//断言

#define MAX(a,b) ((a) > (b) ? (a): (b))

#define MAX_STRING_NUM 20

#define Per_Class(object)  (pthis = (object))
#define Per_Private(object)       ((PersonPrivate*)(object-> inner))

typedef char string[MAX_STRING_NUM];

typedef struct PersonPrivate{
    int age;
    string name;
} PersonPrivate;


typedef struct Person Person;
typedef struct Person
{

    void * inner;
    //方法
    void (*set_age)(const int age);
    void (*set_name)(const string name);
    void (*get_age)(int *age);
    void (*get_name)(string name);
    void (*print_msg)(void);
 
} Person;

Person* pthis = NULL;

void person_set_age(const int age){
    assert(14 < age && age < 30);
    Per_Private(pthis) -> age = age;
}

void person_set_name(const string name){
   strcpy(Per_Private(pthis)>name, name);
}

void person_get_age(int *age){
   *age =  Per_Private(pthis) -> age;
}

void person_get_name(string name){
   strcpy(name, Per_Private(pthis)->name);
}

void person_print_msg(void){
    printf("the person msg is\n{age : %d, name : %s}\n",Per_Private(pthis) -> age, Per_Private(pthis)-> name);
}

Person* CreatPersonClass(void){
    Person* person = (Person *)malloc(sizeof(Person));
    //assert(person != NULL);
    if(person == NULL){
        return NULL;
    }

    person -> inner = malloc(sizeof(PersonPrivate));
    assert(person -> inner);

    person -> set_age   = person_set_age;
    person -> set_name  = person_set_name;
    person -> get_age   = person_get_age;
    person -> get_name  = person_get_name;
    person -> print_msg = person_print_msg;

    pthis = person;
    return person;
 }

Person* CreatPersonClassWithArgs(const int age, const string name){
    Person* person = CreatPersonClass();
    if(person == NULL){
        printf("person null");
        return NULL;
    }
    Per_Private(person) -> age = age;
    strcpy(Per_Private(person) -> name, name);
    return person;
}


int main(void){

    string tmp_name = "Jack";
    int tmp_age = 0;
    Person* jack = CreatPersonClassWithArgs(18,"Jack"); 
    
    jack->set_age(23);
    jack->print_msg();    
    return 0;
}


