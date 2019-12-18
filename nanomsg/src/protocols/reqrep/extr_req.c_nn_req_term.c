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
struct TYPE_2__ {int /*<<< orphan*/  request; int /*<<< orphan*/  reply; int /*<<< orphan*/  timer; } ;
struct nn_req {int /*<<< orphan*/  xreq; int /*<<< orphan*/  fsm; TYPE_1__ task; } ;

/* Variables and functions */
 int /*<<< orphan*/  nn_fsm_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_msg_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_task_term (TYPE_1__*) ; 
 int /*<<< orphan*/  nn_timer_term (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_xreq_term (int /*<<< orphan*/ *) ; 

void nn_req_term (struct nn_req *self)
{
    nn_timer_term (&self->task.timer);
    nn_task_term (&self->task);
    nn_msg_term (&self->task.reply);
    nn_msg_term (&self->task.request);
    nn_fsm_term (&self->fsm);
    nn_xreq_term (&self->xreq);
}