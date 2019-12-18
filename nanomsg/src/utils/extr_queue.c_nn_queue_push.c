#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nn_queue_item {struct nn_queue_item* next; } ;
struct nn_queue {struct nn_queue_item* tail; struct nn_queue_item* head; } ;

/* Variables and functions */
 struct nn_queue_item* NN_QUEUE_NOTINQUEUE ; 
 int /*<<< orphan*/  nn_assert (int) ; 

void nn_queue_push (struct nn_queue *self, struct nn_queue_item *item)
{
    nn_assert (item->next == NN_QUEUE_NOTINQUEUE);

    item->next = NULL;
    if (!self->head)
        self->head = item;
    if (self->tail)
        self->tail->next = item;
    self->tail = item;
}