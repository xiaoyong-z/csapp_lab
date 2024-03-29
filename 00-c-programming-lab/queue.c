/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
  queue_t *q = malloc(sizeof(queue_t));
  /* What if malloc returned NULL? */
  if (q == NULL)
    return NULL;
  q->head = NULL;
  q->tail = q->head;
  q->q_size = 0;
  return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
  /* How about freeing the list elements and the strings? */
  /* Free queue structure */
  if(q == NULL)
    return;
  while (q->q_size > 0)
  {
    list_ele_t *t = q->head;
    q->head = q->head->next;
    free(t->value);
    free(t);
    t = NULL;
    q->q_size -= 1;
    if (q->q_size == 0)
      q->tail = NULL;
  }
  free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if 
  is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
  if (q == NULL)
    return false;
  /* allocate memory for list element */
  list_ele_t *newh;
  newh = malloc(sizeof(list_ele_t));
  if (newh == NULL)
    return false;
  /* allocate memory for value */
  newh->value = malloc(sizeof(char) * (strlen(s) + 1));
  if (newh->value == NULL){
    free(newh);
    return false;
  }
  memcpy(newh->value, s, sizeof(char) * (strlen(s) + 1));
  /* insert the element at head of queue */
  newh->next = q->head;
  q->head = newh;
  if (q->tail == NULL)
    q->tail = q->head;
  q->q_size += 1;
  return true;
}

/*
  Attempt to insert element at tail of queue.
  Return  se if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
  /* You need to write the complete code for this function */
  /* Remember: It should operate in O(1) time */
  if (q == NULL)
    return false;
  /* allocate memory for list element */
  list_ele_t *newh;
  newh = malloc(sizeof(list_ele_t));
  if (newh == NULL)
    return false;
  /* allocate memory for value */
  newh->value = malloc(sizeof(char) * (strlen(s) + 1));
  if (newh->value == NULL){
    free(newh);
    return false;
  }
  memccpy(newh->value, s, sizeof(char) * (strlen(s) + 1), sizeof(char) * (strlen(s) + 1));
  /* insert the element at tail of queue */
  newh->next = NULL;
  if (q->tail != NULL)
    q->tail->next = newh;
  q->tail = newh;
  if (q->head == NULL)
    q->head = q->tail;
  q->q_size += 1;
  return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
  /* Return false if queue is NULL or empty. */
  if (q == NULL || q->q_size == 0)
    return false;
  list_ele_t *t = q->head;
  q->head = q->head->next;
  if(sp != NULL){
    memccpy(sp, t->value, sizeof(char) * (strlen(t->value) + 1), bufsize - 1);
    sp[bufsize - 1] = '\0';
  }
  free(t->value);
  free(t);
  t = NULL;
  /* You need to fix up this code. */
  q->q_size -= 1;
  if (q->q_size == 0)
    q->tail = NULL;
  return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
  /* You need to write the code for this function */
  /* Remember: It should operate in O(1) time */
  if(q == NULL)
    return 0;
  return q->q_size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
  /* You need to write the code for this function */
  if(q == NULL || q->q_size == 0)
    return;
  list_ele_t* t_head = q->head;
  list_ele_t* t_tail = q->tail;
  list_ele_t* t = q->head;
  list_ele_t* t_next = q->head->next;
  t->next = NULL;
  while(t_next != NULL){
    list_ele_t* t_next_next = t_next->next;
    t_next->next = t;
    t = t_next;
    t_next = t_next_next;
  }
  q->head = t_tail;
  q->tail = t_head;
}
