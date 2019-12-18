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
struct nn_fsm_event {int src; int type; int /*<<< orphan*/  srcptr; struct nn_fsm* fsm; } ;
struct nn_fsm {int /*<<< orphan*/  ctx; int /*<<< orphan*/  srcptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_ctx_raise (int /*<<< orphan*/ ,struct nn_fsm_event*) ; 

void nn_fsm_raise_from_src (struct nn_fsm *self, struct nn_fsm_event *event, 
    int src, int type)
{
    event->fsm = self;
    event->src = src;
    event->srcptr = self->srcptr;
    event->type = type;
    nn_ctx_raise (self->ctx, event);
}