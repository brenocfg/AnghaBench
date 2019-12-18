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
struct nn_queue_item {int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_QUEUE_NOTINQUEUE ; 

void nn_queue_item_init (struct nn_queue_item *self)
{
    self->next = NN_QUEUE_NOTINQUEUE;
}