#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * srcptr; int /*<<< orphan*/  src; TYPE_1__* fsm; } ;
struct TYPE_3__ {TYPE_2__ stopped; int /*<<< orphan*/  ctx; } ;
struct nn_sock {TYPE_1__ fsm; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_FSM_ACTION ; 
 int /*<<< orphan*/  NN_SOCK_ACTION_STOPPED ; 
 int /*<<< orphan*/  nn_ctx_raise (int /*<<< orphan*/ ,TYPE_2__*) ; 

void nn_sock_stopped (struct nn_sock *self)
{
    /*  TODO: Do the following in a more sane way. */
    self->fsm.stopped.fsm = &self->fsm;
    self->fsm.stopped.src = NN_FSM_ACTION;
    self->fsm.stopped.srcptr = NULL;
    self->fsm.stopped.type = NN_SOCK_ACTION_STOPPED;
    nn_ctx_raise (self->fsm.ctx, &self->fsm.stopped);
}