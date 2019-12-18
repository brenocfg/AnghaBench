#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct nn_usock {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fsm; int /*<<< orphan*/  src; } ;
struct nn_atcp {int /*<<< orphan*/  fsm; TYPE_1__ listener_owner; struct nn_usock* listener; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_ATCP_SRC_LISTENER ; 
 int /*<<< orphan*/  NN_ATCP_STATE_IDLE ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_atcp*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_usock_swap_owner (struct nn_usock*,TYPE_1__*) ; 

void nn_atcp_start (struct nn_atcp *self, struct nn_usock *listener)
{
    nn_assert_state (self, NN_ATCP_STATE_IDLE);

    /*  Take ownership of the listener socket. */
    self->listener = listener;
    self->listener_owner.src = NN_ATCP_SRC_LISTENER;
    self->listener_owner.fsm = &self->fsm;
    nn_usock_swap_owner (listener, &self->listener_owner);

    /*  Start the state machine. */
    nn_fsm_start (&self->fsm);
}