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
struct nn_ctx {int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_queue_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void nn_ctx_raise (struct nn_ctx *self, struct nn_fsm_event *event)
{
    nn_queue_push (&self->events, &event->item);
}