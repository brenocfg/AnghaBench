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
struct TYPE_2__ {scalar_t__ batch; } ;
struct nn_usock {int /*<<< orphan*/  fsm; int /*<<< orphan*/  wfd; int /*<<< orphan*/  task_connecting; int /*<<< orphan*/  task_connected; int /*<<< orphan*/  task_accept; int /*<<< orphan*/  task_send; int /*<<< orphan*/  task_recv; int /*<<< orphan*/  task_stop; int /*<<< orphan*/  worker; int /*<<< orphan*/  event_established; int /*<<< orphan*/  event_sent; int /*<<< orphan*/  event_received; int /*<<< orphan*/  event_error; TYPE_1__ in; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_USOCK_STATE_IDLE ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_usock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_free (scalar_t__) ; 
 int /*<<< orphan*/  nn_fsm_event_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_worker_cancel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_worker_fd_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_worker_task_term (int /*<<< orphan*/ *) ; 

void nn_usock_term (struct nn_usock *self)
{
    nn_assert_state (self, NN_USOCK_STATE_IDLE);

    if (self->in.batch)
        nn_free (self->in.batch);

    nn_fsm_event_term (&self->event_error);
    nn_fsm_event_term (&self->event_received);
    nn_fsm_event_term (&self->event_sent);
    nn_fsm_event_term (&self->event_established);

    nn_worker_cancel (self->worker, &self->task_stop);
    nn_worker_cancel (self->worker, &self->task_recv);
    nn_worker_cancel (self->worker, &self->task_send);
    nn_worker_cancel (self->worker, &self->task_accept);
    nn_worker_cancel (self->worker, &self->task_connected);
    nn_worker_cancel (self->worker, &self->task_connecting);

    nn_worker_task_term (&self->task_stop);
    nn_worker_task_term (&self->task_recv);
    nn_worker_task_term (&self->task_send);
    nn_worker_task_term (&self->task_accept);
    nn_worker_task_term (&self->task_connected);
    nn_worker_task_term (&self->task_connecting);
    nn_worker_fd_term (&self->wfd);

    nn_fsm_term (&self->fsm);
}