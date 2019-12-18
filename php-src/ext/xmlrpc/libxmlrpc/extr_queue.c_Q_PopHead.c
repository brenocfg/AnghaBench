#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ size; int /*<<< orphan*/  sorted; TYPE_2__* head; TYPE_2__* cursor; TYPE_2__* tail; } ;
typedef  TYPE_1__ queue ;
struct TYPE_7__ {int /*<<< orphan*/ * prev; int /*<<< orphan*/ * next; void* data; } ;
typedef  TYPE_2__ node ;
typedef  int /*<<< orphan*/  datanode ;

/* Variables and functions */
 int /*<<< orphan*/  False_ ; 
 scalar_t__ Q_IsEmpty (TYPE_1__*) ; 
 int /*<<< orphan*/  efree (TYPE_2__*) ; 

void *Q_PopHead(queue *q)
{
   datanode    *n;
   void        *d;

   if(Q_IsEmpty(q))
      return NULL;

   d = q->head->data;
   n = q->head->next;
   efree(q->head);

   q->size--;

   if(q->size == 0)
      q->head = q->tail = q->cursor = NULL;
   else {
      q->head = (node *)n;
      q->head->prev = NULL;
      q->cursor = q->head;
   }

   q->sorted = False_;

   return d;
}