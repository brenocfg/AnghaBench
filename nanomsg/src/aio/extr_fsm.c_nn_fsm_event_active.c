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
struct nn_fsm_event {int /*<<< orphan*/  item; } ;

/* Variables and functions */
 int nn_queue_item_isinqueue (int /*<<< orphan*/ *) ; 

int nn_fsm_event_active (struct nn_fsm_event *self)
{
    return nn_queue_item_isinqueue (&self->item);
}