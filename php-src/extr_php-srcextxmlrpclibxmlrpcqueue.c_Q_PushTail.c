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
struct TYPE_4__ {scalar_t__ size; int sorted; TYPE_2__* tail; TYPE_2__* cursor; TYPE_2__* head; } ;
typedef  TYPE_1__ queue ;
struct TYPE_5__ {void* data; struct TYPE_5__* next; int /*<<< orphan*/ * prev; } ;
typedef  TYPE_2__ node ;
typedef  int /*<<< orphan*/  datanode ;

/* Variables and functions */
 int False_ ; 
 int True_ ; 
 int /*<<< orphan*/ * emalloc (int) ; 

int Q_PushTail(queue *q, void *d)
{
   if(q && d) {
      node        *p;
      datanode    *n;

      n = emalloc(sizeof(datanode));
      if(n == NULL)
         return False_;

      p = q->tail;
      q->tail = (node *)n;

      if(q->size == 0) {
         q->tail->prev = NULL;
         q->head = q->tail;
      }
      else {
         q->tail->prev = (datanode *)p;
         p->next = q->tail;
      }

      q->tail->next = NULL;

      q->tail->data =  d;
      q->cursor = q->tail;
      q->size++;

      q->sorted = False_;

      return True_;
   }
   return False_;
}