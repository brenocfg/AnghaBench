#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ size; int sorted; TYPE_2__* head; TYPE_2__* cursor; TYPE_2__* tail; } ;
typedef  TYPE_1__ queue ;
struct TYPE_5__ {void* data; struct TYPE_5__* prev; int /*<<< orphan*/ * next; } ;
typedef  TYPE_2__ node ;
typedef  int /*<<< orphan*/  datanode ;

/* Variables and functions */
 int False_ ; 
 int True_ ; 
 int /*<<< orphan*/ * emalloc (int) ; 

int Q_PushHead(queue *q, void *d)
{
   if(q && d) {
      node    *n;
      datanode *p;

      p = emalloc(sizeof(datanode));
      if(p == NULL)
         return False_;

      n = q->head;

      q->head = (node*)p;
      q->head->prev = NULL;

      if(q->size == 0) {
         q->head->next = NULL;
         q->tail = q->head;
      }
      else {
         q->head->next = (datanode*)n;
         n->prev = q->head;
      }

      q->head->data = d;
      q->size++;

      q->cursor = q->head;

      q->sorted = False_;

      return True_;
   }
   return False_;
}