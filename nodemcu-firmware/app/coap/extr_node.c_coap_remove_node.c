#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ coap_tid_t ;
struct TYPE_4__ {scalar_t__ const id; scalar_t__ t; struct TYPE_4__* next; } ;
typedef  TYPE_1__ coap_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  coap_delete_node (TYPE_1__*) ; 

int coap_remove_node( coap_queue_t **queue, const coap_tid_t id){
  coap_queue_t *p, *q, *node;
  if ( !queue )
    return 0;
  if ( !*queue )  // if empty
    return 0;

  q = *queue;
  if (q->id == id) {
    node = q;
    *queue = q->next;
    node->next = NULL;
    if(*queue){
      (*queue)->t += node->t;
    }
    coap_delete_node(node);
    return 1;
  }

  /* search for right node to remove */
  while (q && q->id != id) {
    p = q;
    q = q->next;
  }

  /* find the node */
  if (q) {
    node = q; /* save the node */
    p->next = q->next;  /* remove the node */
    q = q->next;
    node->next = NULL;
    if (q)   // add node->t to the node after.
    {
      q->t += node->t;
    }
    coap_delete_node(node);
    return 1;
  }
  return 0;
}