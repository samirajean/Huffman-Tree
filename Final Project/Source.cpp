#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
 
#define MAX_TREE_HT 100 //Max hieght of huffman tree
 
struct MinHeapNode
{
    char data;  
	unsigned freq;
    struct MinHeapNode *left, *right;
};
 
struct MinHeap
{
    unsigned size;   //unsigned cause it doesn't have a specific value
    unsigned capacity; 
    struct MinHeapNode **array;
};
 
struct MinHeapNode* newNode(char data, unsigned freq) //allocating a new node with character and it's freq
{
    struct MinHeapNode* temp = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}
 
struct MinHeap* createMinHeap(unsigned capacity) //creating a minheap of a given capacity
{
    struct MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->size = 0; 
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}
 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) //swaping two nodes "will in minheapify fun"
{
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}
 
void minHeapify(struct MinHeap* minHeap, int idx) //to get the min minheap
{
    int smallest = idx; //asumed that the smallest is equal idx
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
 
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
      smallest = left;
 
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
      smallest = right;
 
    if (smallest != idx)
    {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}
 

int isSizeOne(struct MinHeap* minHeap) //will be used in buildhuffmantree function to iterate will the size !=1
{
    return (minHeap->size == 1);
}


struct MinHeapNode* extractMin(struct MinHeap* minHeap) //extracting the minimum heap node
{
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}
 
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) //inserting a new node to min heap
{
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1)/2]->freq)
    {
        minHeap->array[i] = minHeap->array[(i - 1)/2];
        i = (i - 1)/2; //to find the place of the min heap node
    }
	//the loop will compare the node and its freq till i < 0
    minHeap->array[i] = minHeapNode; //then it will be put in the right location
}
 
void buildMinHeap(struct MinHeap* minHeap) //building a sorted min heap tree therefore we used minheapify to sort
{
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}
 
void printArr(int arr[], int n) // printing an array of size n
{
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}
 
int isLeaf(struct MinHeapNode* root)// the leaf is the one who contains data this will be used in printcodes fun
{
    return !(root->left) && !(root->right) ;
}

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) //inserts all the characters in data[] in min heap..intially size = capacity
{
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}
 

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) //building the huffman tree
{
    struct MinHeapNode *left, *right, *top;
 
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
 
   
    while (!isSizeOne(minHeap))
    {
        left = extractMin(minHeap);
		                             //extracting the two min freq
        right = extractMin(minHeap);
 

        top = newNode('$', left->freq + right->freq); //$ is special value of internal nodes...NOT USED  
		//we add the left and right frequencies and the sum is the new node's val
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}
 
void printCodes(struct MinHeapNode* root, int arr[], int top)
{
    if (root->left)
    {
        arr[top] = 0; //asigning 0
        printCodes(root->left, arr, top + 1);
    }
 
    if (root->right)
    {
        arr[top] = 1; //assigning 1
        printCodes(root->right, arr, top + 1);
    }
 
    if (isLeaf(root)) //using is leaf function
    {
        printf("%c: ", root->data); 
        printArr(arr, top);
    }
}
 
void HuffmanCodes(char data[], int freq[], int size) //building and printing the huffman codes and characters
{
   
   struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
 
   int arr[MAX_TREE_HT], top = 0;
   printCodes(root, arr, top);
}
 
int main()
{
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(arr)/sizeof(arr[0]);
    HuffmanCodes(arr, freq, size);
	getch();
    return 0;
}