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
struct nn_fsm {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_FSM_STATE_IDLE ; 
 int /*<<< orphan*/  NN_FSM_STATE_STOPPING ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_fsm*,int /*<<< orphan*/ ) ; 

void nn_fsm_stopped_noevent (struct nn_fsm *self)
{
    nn_assert_state (self, NN_FSM_STATE_STOPPING);
    self->state = NN_FSM_STATE_IDLE;
}