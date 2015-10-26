/* Find k-th element descending in Binary Search Tree */
// Напишите функцию, принимающую в качестве параметра указатель на корень двоичного дерева поиска и число k.
// Функция должна возвращать значения поля Key k-ого элемента при сортировке их по убыванию.
#include <iostream>

struct TNode {
    TNode* Parent;
    TNode* Left;
    TNode* Right;
    int Key;
};

TNode *newNode(int item, TNode* parent)
{
    TNode *temp = new TNode;
    temp->Key = item;
    temp->Left = temp->Right = NULL;
    temp->Parent = parent;
    return temp;
}

TNode* insert(TNode* node, int key, TNode* parent = NULL)
{
    if (node == NULL) return newNode(key, parent);

    if (key < node->Key)
        node->Left  = insert(node->Left, key, node);
    else if (key > node->Key)
        node->Right = insert(node->Right, key, node);

    return node;
}

// A function to find k'th largest element in a given tree.
void kthLargestUtil(TNode *root, int k, int &c)
{
    // Base cases, the second condition is important to
    // avoid unnecessary recursive calls
    if (root == NULL || c >= k)
        return;

    // Follow reverse inorder traversal so that the
    // largest element is visited first
    kthLargestUtil(root->Right, k, c);

    // Increment count of visited nodes
    c++;

    // If c becomes k now, then this is the k'th largest
    if (c == k)
    {
        std::cout << "K'th largest element is " << root->Key << std::endl;
        return;
    }

    // Recur for left subtree
    kthLargestUtil(root->Left, k, c);
}

// Function to find k'th largest element
void kthLargest(TNode *root, int k)
{
    // Initialize count of nodes visited as 0
    int c = 0;

    // Note that c is passed by reference
    kthLargestUtil(root, k, c);
}

int findKthLargest(TNode *root, int k) {
    TNode *prev = NULL;
    TNode *current = root;

    while(current->Right != NULL) {
        prev = current;
        current = current->Right;
    }

    while(k != 0) {
        if (current == NULL)
            return -1;

        // perv == NULL на самом деле здесь не нужен
        if(prev == current->Right || prev == NULL)
        {
            --k;
            prev = current;
            if(current->Left != NULL)
                current = current->Left;
            else
                current = current->Parent;
        }
        else if(prev == current->Left)
        {
            prev = current;
            current = current->Parent;
        }
        else if(prev == current->Parent)
        {
            prev = current;
            if(current->Right != NULL)
                current = current->Right;
            else if(current->Left != NULL) {
                --k;
                current = current->Left;
            } else {
                --k;
                current = current->Parent;
            }
        }
    }

    return prev->Key;
}

// Driver Program to test above functions
int main()
{
    /* Let us create following BST
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 */
    TNode *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    //insert(root, 40);
    //insert(root, 70);
    //insert(root, 60);
    //insert(root, 80);

    for (int k=1; k<=7; k++)
        kthLargest(root, k);

    for (int k=1; k<=7; k++)
        std::cout << k << "-th largest is " << findKthLargest(root,k) << std::endl;

    return 0;
}
