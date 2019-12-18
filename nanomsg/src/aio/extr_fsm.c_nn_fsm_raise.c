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
struct nn_fsm_event {int type; int /*<<< orphan*/  srcptr; int /*<<< orphan*/  src; int /*<<< orphan*/  fsm; } ;
struct nn_fsm {int /*<<< orphan*/  ctx; int /*<<< orphan*/  srcptr; int /*<<< orphan*/  src; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_ctx_raise (int /*<<< orphan*/ ,struct nn_fsm_event*) ; 

void nn_fsm_raise (struct nn_fsm *self, struct nn_fsm_event *event, int type)
{
    event->fsm = self->owner;
    event->src = self->src;
    event->srcptr = self->srcptr;
    event->type = type;
    nn_ctx_raise (self->ctx, event);
}