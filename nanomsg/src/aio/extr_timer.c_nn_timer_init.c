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
struct nn_timer {int timeout; int /*<<< orphan*/  fsm; int /*<<< orphan*/  worker; int /*<<< orphan*/  done; int /*<<< orphan*/  wtimer; int /*<<< orphan*/  stop_task; int /*<<< orphan*/  start_task; int /*<<< orphan*/  state; } ;
struct nn_fsm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_TIMER_SRC_START_TASK ; 
 int /*<<< orphan*/  NN_TIMER_SRC_STOP_TASK ; 
 int /*<<< orphan*/  NN_TIMER_STATE_IDLE ; 
 int /*<<< orphan*/  nn_fsm_choose_worker (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_event_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct nn_timer*,struct nn_fsm*) ; 
 int /*<<< orphan*/  nn_timer_handler ; 
 int /*<<< orphan*/  nn_timer_shutdown ; 
 int /*<<< orphan*/  nn_worker_task_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_worker_timer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void nn_timer_init (struct nn_timer *self, int src, struct nn_fsm *owner)
{
    nn_fsm_init (&self->fsm, nn_timer_handler, nn_timer_shutdown,
        src, self, owner);
    self->state = NN_TIMER_STATE_IDLE;
    nn_worker_task_init (&self->start_task, NN_TIMER_SRC_START_TASK,
        &self->fsm);
    nn_worker_task_init (&self->stop_task, NN_TIMER_SRC_STOP_TASK, &self->fsm);
    nn_worker_timer_init (&self->wtimer, &self->fsm);
    nn_fsm_event_init (&self->done);
    self->worker = nn_fsm_choose_worker (&self->fsm);
    self->timeout = -1;
}