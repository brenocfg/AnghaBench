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
struct nn_usock {int /*<<< orphan*/  event_error; int /*<<< orphan*/  fsm; int /*<<< orphan*/  task_stop; int /*<<< orphan*/  worker; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_USOCK_SHUTDOWN ; 
 int /*<<< orphan*/  nn_fsm_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_worker_execute (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nn_usock_async_stop (struct nn_usock *self)
{
    nn_worker_execute (self->worker, &self->task_stop);
    nn_fsm_raise (&self->fsm, &self->event_error, NN_USOCK_SHUTDOWN);
}