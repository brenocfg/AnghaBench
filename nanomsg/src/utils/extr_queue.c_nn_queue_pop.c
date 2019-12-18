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
struct nn_queue {int /*<<< orphan*/ * tail; struct nn_queue_item* head; } ;

/* Variables and functions */
 struct nn_queue_item* NN_QUEUE_NOTINQUEUE ; 

struct nn_queue_item *nn_queue_pop (struct nn_queue *self)
{
    struct nn_queue_item *result;

    if (!self->head)
        return NULL;
    result = self->head;
    self->head = result->next;
    if (!self->head)
        self->tail = NULL;
    result->next = NN_QUEUE_NOTINQUEUE;
    return result;
}