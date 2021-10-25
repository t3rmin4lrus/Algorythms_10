#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* next;
    char data;
} Node;

typedef struct {
    Node* head;
    unsigned int size;
} MyList;

int PushStack(MyList* stack, char data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf(stderr, "Stack overflow!\n");
        return 0;
    }
    node->data = data;
    node->next = stack->head;
    stack->head = node;
    stack->size++;
    return 1;
}

char Pop(MyList* list)
{
    char data;
    Node* tmp;

    if (list->size == 0)
        return -1;
    data = list->head->data;
    tmp = list->head;
    list->size--;
    if (list->size == 0) {
        list->head = NULL;
    }
    else {
        list->head = list->head->next;
    }
    free(tmp);
    return data;
}

void initList(MyList* list)
{
    list->head = NULL;
    list->size = 0;
}

void releaseList(MyList* list)
{
    Node* tmp;

    while (list->size > 0) {
        tmp = list->head;
        list->size--;
        if (list->size > 0)
            list->head = list->head->next;
        free(tmp);
    }
    free(list);
}

char fillBracket(char brackets) {
    switch (brackets) {
    case ')':
        return '(';
    case ']':
        return '[';
    case '}':
        return '{';
    }
    return '\0';
}

int brackBalance(char* line)
{
    char x, fillBrackets;
    MyList* bracketsStack = (MyList*)malloc(sizeof(MyList));

    for (int i = 0; (x = line[i]) != '\0'; i++) {
        switch (x) {
        case '(':
        case '[':
        case '{':
            if (!PushStack(bracketsStack, x))
                return 0;
            break;
        case ')':
        case ']':
        case '}':
            fillBrackets = Pop(bracketsStack);
            if (fillBrackets != '\0' && fillBrackets == fillBracket(x))
                continue;
            else
                return 0;
        }
    }
    if (bracketsStack->size != 0)
        return 0;
    releaseList(bracketsStack);
    return 1;
}

void printedList(MyList* list)
{
    int listSize = list->size;
    Node* current = list->head;

    while (listSize > 0) {
        printf("[%c]", current->data);
        listSize--;
        if (listSize > 0)
            current = current->next;
    }
    printf("\n");
}

int copyLinkList(MyList* main, MyList* dat)
{
    int datListSize = dat->size;
    Node* datCurrentNode = dat->head;
    Node* mainCurrentNode = main->head;

    while (datListSize > 0) {
        Node* mainNewNode = (Node*)malloc(sizeof(Node));
        if (mainNewNode == NULL)
            return 0;
        mainNewNode->data = datCurrentNode->data;
        mainNewNode->next = NULL;
        if (main->size == 0) {
            main->head = mainNewNode;
        }
        else {
            mainCurrentNode->next = mainNewNode;
        }
        mainCurrentNode = mainNewNode;
        main->size++;
        datListSize--;
        if (datListSize > 0)
            datCurrentNode = datCurrentNode->next;
    }
    return 1;
}

int listSorted(MyList* list)
{
    int listSize = list->size;
    Node* current = list->head;
    char max;

    while (listSize > 0) {
        if (current == list->head)
            max = current->data;
        if (current->data >= max) {
            max = current->data;
        }
        else {
            return 0;
        }
        listSize--;
        if (listSize > 0)
            current = current->next;
    }
    return 1;
}

int main()
{
    char* myBrackets[] = {"()", "([])()", "{}()", "([{}])", ")(", "())({)", "(", "]})", "([(])", "(2+(2*))", "[2/{5*(4+7)}]", NULL};

    printf("Balance of brackets:\n");

    for (int i = 0; myBrackets[i] != NULL; i++) {
        printf("\t brackets are %s balanced!\n", myBrackets[i],
            brackBalance(myBrackets[i]) ? "\b" : "not");
    }

    MyList* Mylist = (MyList*)malloc(sizeof(MyList));
    MyList* copyList = (MyList*)malloc(sizeof(MyList));

    printf("\n Copy of list:\n");

    initList(Mylist);
    PushStack(Mylist, 'o');
    PushStack(Mylist, 'd');
    PushStack(Mylist, 'l');
    PushStack(Mylist, 'b');
    PushStack(Mylist, 'o');

    initList(copyList);
    if (!copyLinkList(copyList, Mylist)) {
        printf(stderr, "Error!\n");
        return 1;
    }

    printf("Usual list:\n\t");
    printedList(Mylist);

    printf("Copy of list:\n\t");
    printedList(copyList);

    releaseList(Mylist);
    releaseList(copyList);

    MyList* sortedList = (MyList*)malloc(sizeof(MyList));
    MyList* unsortedList = (MyList*)malloc(sizeof(MyList));
    MyList* myLists[] = {sortedList, unsortedList};

    printf("\n Checking the list for sorting:\n");

    initList(myLists[0]);
    PushStack(myLists[0], 'w');
    PushStack(myLists[0], 'h');
    PushStack(myLists[0], 'n');
    PushStack(myLists[0], 'f');
    PushStack(myLists[0], 'u');
    PushStack(myLists[0], 'u');
    PushStack(myLists[0], 'a');

    initList(myLists[1]);
    PushStack(myLists[1], 'a');
    PushStack(myLists[1], 'a');
    PushStack(myLists[1], 'k');
    PushStack(myLists[1], 'q');
    PushStack(myLists[1], 'c');
    PushStack(myLists[1], 'b');
    PushStack(myLists[1], 't');

    for (int i = 0; i < 2; i++) {
        printedList(myLists[i]);
        printf("\tlist is %s sorted!\n",
            listSorted(myLists[i]) ? "\b" : "not");
        releaseList(myLists[i]);
    }

    return 0;
}
