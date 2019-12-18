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
struct nn_sockbase_vfptr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  timer; int /*<<< orphan*/  reply; int /*<<< orphan*/  request; int /*<<< orphan*/ * sent_to; } ;
struct TYPE_3__ {int /*<<< orphan*/  sockbase; } ;
struct nn_req {int /*<<< orphan*/  fsm; int /*<<< orphan*/  lastid; TYPE_2__ task; int /*<<< orphan*/  resend_ivl; int /*<<< orphan*/  state; TYPE_1__ xreq; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_REQ_DEFAULT_RESEND_IVL ; 
 int /*<<< orphan*/  NN_REQ_SRC_RESEND_TIMER ; 
 int /*<<< orphan*/  NN_REQ_STATE_IDLE ; 
 int /*<<< orphan*/  nn_fsm_init_root (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_msg_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_random_generate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nn_req_handler ; 
 int /*<<< orphan*/  nn_req_shutdown ; 
 int /*<<< orphan*/  nn_sockbase_getctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_task_init (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_timer_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_xreq_init (TYPE_1__*,struct nn_sockbase_vfptr const*,void*) ; 

void nn_req_init (struct nn_req *self,
    const struct nn_sockbase_vfptr *vfptr, void *hint)
{
    nn_xreq_init (&self->xreq, vfptr, hint);
    nn_fsm_init_root (&self->fsm, nn_req_handler, nn_req_shutdown,
        nn_sockbase_getctx (&self->xreq.sockbase));
    self->state = NN_REQ_STATE_IDLE;

    /*  Start assigning request IDs beginning with a random number. This way
        there should be no key clashes even if the executable is re-started. */
    nn_random_generate (&self->lastid, sizeof (self->lastid));

    self->task.sent_to = NULL;

    nn_msg_init (&self->task.request, 0);
    nn_msg_init (&self->task.reply, 0);
    nn_timer_init (&self->task.timer, NN_REQ_SRC_RESEND_TIMER, &self->fsm);
    self->resend_ivl = NN_REQ_DEFAULT_RESEND_IVL;

    nn_task_init (&self->task, self->lastid);

    /*  Start the state machine. */
    nn_fsm_start (&self->fsm);
}