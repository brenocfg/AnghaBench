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
struct nn_fsm_event {int src; int type; void* srcptr; struct nn_fsm* fsm; } ;
struct nn_fsm {int /*<<< orphan*/  ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_ctx_raiseto (int /*<<< orphan*/ ,struct nn_fsm_event*) ; 

void nn_fsm_raiseto (struct nn_fsm *self, struct nn_fsm *dst,
    struct nn_fsm_event *event, int src, int type, void *srcptr)
{
    event->fsm = dst;
    event->src = src;
    event->srcptr = srcptr;
    event->type = type;
    nn_ctx_raiseto (self->ctx, event);
}