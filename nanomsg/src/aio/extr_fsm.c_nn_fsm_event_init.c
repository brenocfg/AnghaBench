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
struct nn_fsm_event {int src; int type; int /*<<< orphan*/  item; int /*<<< orphan*/ * srcptr; int /*<<< orphan*/ * fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_queue_item_init (int /*<<< orphan*/ *) ; 

void nn_fsm_event_init (struct nn_fsm_event *self)
{
    self->fsm = NULL;
    self->src = -1;
    self->srcptr = NULL;
    self->type = -1;
    nn_queue_item_init (&self->item);
}