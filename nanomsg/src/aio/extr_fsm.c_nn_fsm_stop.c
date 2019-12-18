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
struct nn_fsm {scalar_t__ state; int /*<<< orphan*/  (* shutdown_fn ) (struct nn_fsm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NN_FSM_ACTION ; 
 scalar_t__ NN_FSM_STATE_ACTIVE ; 
 scalar_t__ NN_FSM_STATE_STOPPING ; 
 int /*<<< orphan*/  NN_FSM_STOP ; 
 int /*<<< orphan*/  stub1 (struct nn_fsm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nn_fsm_stop (struct nn_fsm *self)
{
    /*  If stopping of the state machine was already requested, do nothing. */
    if (self->state != NN_FSM_STATE_ACTIVE)
        return;

    self->state = NN_FSM_STATE_STOPPING;
    self->shutdown_fn (self, NN_FSM_ACTION, NN_FSM_STOP, NULL);
}