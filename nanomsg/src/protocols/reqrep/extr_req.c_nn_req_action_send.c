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
struct TYPE_4__ {struct nn_pipe* sent_to; int /*<<< orphan*/  timer; int /*<<< orphan*/  request; } ;
struct TYPE_3__ {int /*<<< orphan*/  sockbase; } ;
struct nn_req {int /*<<< orphan*/  state; TYPE_2__ task; int /*<<< orphan*/  resend_ivl; TYPE_1__ xreq; } ;
struct nn_pipe {int dummy; } ;
struct nn_msg {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  NN_REQ_STATE_ACTIVE ; 
 int /*<<< orphan*/  NN_REQ_STATE_DELAYED ; 
 int /*<<< orphan*/  errnum_assert (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 scalar_t__ nn_fast (int) ; 
 int /*<<< orphan*/  nn_msg_cp (struct nn_msg*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_msg_term (struct nn_msg*) ; 
 scalar_t__ nn_slow (int) ; 
 int /*<<< orphan*/  nn_timer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nn_xreq_send_to (int /*<<< orphan*/ *,struct nn_msg*,struct nn_pipe**) ; 

void nn_req_action_send (struct nn_req *self, int allow_delay)
{
    int rc;
    struct nn_msg msg;
    struct nn_pipe *to;

    /*  Send the request. */
    nn_msg_cp (&msg, &self->task.request);
    rc = nn_xreq_send_to (&self->xreq.sockbase, &msg, &to);

    /*  If the request cannot be sent at the moment wait till
        new outbound pipe arrives. */
    if (nn_slow (rc == -EAGAIN)) {
        nn_assert (allow_delay == 1);
        nn_msg_term (&msg);
        self->state = NN_REQ_STATE_DELAYED;
        return;
    }

    /*  Request was successfully sent. Set up the re-send timer
        in case the request gets lost somewhere further out
        in the topology. */
    if (nn_fast (rc == 0)) {
        nn_timer_start (&self->task.timer, self->resend_ivl);
        nn_assert (to);
        self->task.sent_to = to;
        self->state = NN_REQ_STATE_ACTIVE;
        return;
    }

    /*  Unexpected error. */
    errnum_assert (0, -rc);
}