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
struct nn_fsm {scalar_t__ state; int /*<<< orphan*/  stopped; } ;

/* Variables and functions */
 scalar_t__ NN_FSM_STATE_IDLE ; 
 int /*<<< orphan*/  nn_fsm_event_active (int /*<<< orphan*/ *) ; 

int nn_fsm_isidle (struct nn_fsm *self)
{
    return self->state == NN_FSM_STATE_IDLE &&
        !nn_fsm_event_active (&self->stopped) ? 1 : 0;
}