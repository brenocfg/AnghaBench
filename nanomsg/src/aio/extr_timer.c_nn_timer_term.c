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
struct nn_timer {int /*<<< orphan*/  fsm; int /*<<< orphan*/  start_task; int /*<<< orphan*/  stop_task; int /*<<< orphan*/  wtimer; int /*<<< orphan*/  done; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_TIMER_STATE_IDLE ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_event_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_worker_task_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_worker_timer_term (int /*<<< orphan*/ *) ; 

void nn_timer_term (struct nn_timer *self)
{
    nn_assert_state (self, NN_TIMER_STATE_IDLE);

    nn_fsm_event_term (&self->done);
    nn_worker_timer_term (&self->wtimer);
    nn_worker_task_term (&self->stop_task);
    nn_worker_task_term (&self->start_task);
    nn_fsm_term (&self->fsm);
}