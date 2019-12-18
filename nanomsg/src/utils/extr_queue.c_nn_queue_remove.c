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
struct nn_queue_item {scalar_t__ next; } ;
struct nn_queue {struct nn_queue_item* tail; struct nn_queue_item* head; } ;

/* Variables and functions */
 scalar_t__ NN_QUEUE_NOTINQUEUE ; 

void nn_queue_remove (struct nn_queue *self, struct nn_queue_item *item)
{
    struct nn_queue_item *it;
    struct nn_queue_item *prev;

    if (item->next == NN_QUEUE_NOTINQUEUE)
        return;

    prev = NULL;
    for (it = self->head; it != NULL; it = it->next) {
        if (it == item) {
            if (self->head == it)
                self->head = it->next;
            if (self->tail == it)
                self->tail = prev;
            if (prev)
                prev->next = it->next;
            item->next = NN_QUEUE_NOTINQUEUE;
            return;
        }
        prev = it;
    }
}