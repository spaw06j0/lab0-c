#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Notice: sometimes, Cppcheck would find the potential NULL pointer bugs,
 * but some of them cannot occur. You can suppress them by adding the
 * following line.
 *   cppcheck-suppress nullPointer
 */


/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head =
        (struct list_head *) malloc(sizeof(struct list_head));
    if (!head) {
        printf("malloc failed\n");
        return NULL;
    }
    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    // iterate the doubly linked list: free the memory of each node and list_del
    // consider the case that head is NULL
    if (!head) {
        return;
    }
    struct list_head *node, *tmp;
    // free the memory of entry by call the function q_release_element
    list_for_each_safe (node, tmp, head) {
        element_t *entry = list_entry(node, element_t, list);
        q_release_element(entry);
    }
    free(head);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    // check the head and the string s
    if (!head || !s) {
        return false;
    }
    element_t *element = (element_t *) malloc(sizeof(element_t));
    if (!element) {
        return false;
    }
    element->value = (char *) malloc(strlen(s) + 1);
    if (!element->value) {
        free(element);
        return false;
    }
    strncpy(element->value, s, strlen(s) + 1);
    list_add(&element->list, head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head || !s) {
        return false;
    }
    element_t *element = (element_t *) malloc(sizeof(element_t));
    if (!element) {
        return false;
    }
    element->value = (char *) malloc(strlen(s) + 1);
    if (!element->value) {
        free(element);
        return false;
    }
    strncpy(element->value, s, strlen(s) + 1);
    list_add_tail(&element->list, head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head)) {
        return NULL;
    }
    struct list_head *node = head->next;
    list_del(node);
    element_t *element = list_entry(node, element_t, list);
    // copy the removed string to *sp
    if (sp && element->value) {
        strncpy(sp, element->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    return element;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head)) {
        return NULL;
    }
    struct list_head *node = head->prev;
    list_del(node);
    element_t *element = list_entry(node, element_t, list);
    if (sp && element->value) {
        strncpy(sp, element->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    return element;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head || list_empty(head)) {
        return 0;
    }
    int count = 0;
    struct list_head *node;
    list_for_each (node, head) {
        count++;
    }
    return count;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    // https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
    if (!head || list_empty(head)) {
        return false;
    }
    int mid = q_size(head) / 2;
    int i = 0;
    struct list_head *node, *safe;
    list_for_each_safe (node, safe, head) {
        if (i == mid) {
            list_del(node);
            element_t *element = list_entry(node, element_t, list);
            q_release_element(element);
            break;
        }
        i++;
    }
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    if (!head || list_empty(head)) {
        return false;
    }
    struct list_head *node, *safe, *temp;
    list_for_each_safe (node, safe, head) {
        element_t *entry = list_entry(node, element_t, list);
        bool is_dup = false;
        list_for_each_safe (temp, safe, &entry->list) {
            element_t *entry_temp = list_entry(temp, element_t, list);
            if (strcmp(entry->value, entry_temp->value) == 0) {
                is_dup = true;
                list_del(temp);
                q_release_element(entry_temp);
            }
        }
        if (is_dup) {
            list_del(node);
            q_release_element(entry);
        }
    }
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    // https://leetcode.com/problems/swap-nodes-in-pairs/
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head) {}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
