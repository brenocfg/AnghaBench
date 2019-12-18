#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int msg_iovlen; TYPE_1__* msg_iov; } ;
struct TYPE_5__ {TYPE_3__ hdr; TYPE_1__* iov; } ;
struct nn_usock {scalar_t__ state; int /*<<< orphan*/  task_send; int /*<<< orphan*/  worker; int /*<<< orphan*/  fsm; int /*<<< orphan*/  event_sent; TYPE_2__ out; } ;
struct nn_iovec {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;
struct TYPE_4__ {scalar_t__ iov_len; int /*<<< orphan*/  iov_base; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ECONNRESET ; 
 int /*<<< orphan*/  NN_USOCK_ACTION_ERROR ; 
 int NN_USOCK_MAX_IOVCNT ; 
 int /*<<< orphan*/  NN_USOCK_SENT ; 
 scalar_t__ NN_USOCK_STATE_ACTIVE ; 
 int /*<<< orphan*/  errnum_assert (int,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 scalar_t__ nn_fast (int) ; 
 int /*<<< orphan*/  nn_fsm_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nn_slow (int) ; 
 int nn_usock_send_raw (struct nn_usock*,TYPE_3__*) ; 
 int /*<<< orphan*/  nn_worker_execute (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nn_usock_send (struct nn_usock *self, const struct nn_iovec *iov,
    int iovcnt)
{
    int rc;
    int i;
    int out;

    /*  Make sure that the socket is actually alive. */
    if (self->state != NN_USOCK_STATE_ACTIVE) {
        nn_fsm_action (&self->fsm, NN_USOCK_ACTION_ERROR);
        return;
    }

    /*  Copy the iovecs to the socket. */
    nn_assert (iovcnt <= NN_USOCK_MAX_IOVCNT);
    self->out.hdr.msg_iov = self->out.iov;
    out = 0;
    for (i = 0; i != iovcnt; ++i) {
        if (iov [i].iov_len == 0)
            continue;
        self->out.iov [out].iov_base = iov [i].iov_base;
        self->out.iov [out].iov_len = iov [i].iov_len;
        out++;
    }
    self->out.hdr.msg_iovlen = out;

    /*  Try to send the data immediately. */
    rc = nn_usock_send_raw (self, &self->out.hdr);

    /*  Success. */
    if (nn_fast (rc == 0)) {
        nn_fsm_raise (&self->fsm, &self->event_sent, NN_USOCK_SENT);
        return;
    }

    /*  Errors. */
    if (nn_slow (rc != -EAGAIN)) {
        errnum_assert (rc == -ECONNRESET, -rc);
        nn_fsm_action (&self->fsm, NN_USOCK_ACTION_ERROR);
        return;
    }

    /*  Ask the worker thread to send the remaining data. */
    nn_worker_execute (self->worker, &self->task_send);
}