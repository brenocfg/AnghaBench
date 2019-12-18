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
struct nn_usock {scalar_t__ errnum; int /*<<< orphan*/  task_accept; int /*<<< orphan*/  worker; int /*<<< orphan*/  event_error; int /*<<< orphan*/  fsm; int /*<<< orphan*/  state; struct nn_usock* asock; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ ECONNABORTED ; 
 scalar_t__ EMFILE ; 
 scalar_t__ ENFILE ; 
 scalar_t__ ENOBUFS ; 
 scalar_t__ ENOMEM ; 
 scalar_t__ ENOTSUP ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  NN_USOCK_ACCEPT_ERROR ; 
 int /*<<< orphan*/  NN_USOCK_ACTION_ACCEPT ; 
 int /*<<< orphan*/  NN_USOCK_ACTION_BEING_ACCEPTED ; 
 int /*<<< orphan*/  NN_USOCK_ACTION_DONE ; 
 int /*<<< orphan*/  NN_USOCK_STATE_ACCEPTING_ERROR ; 
 int /*<<< orphan*/  SOCK_CLOEXEC ; 
 int accept (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int accept4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 scalar_t__ nn_fast (int) ; 
 int /*<<< orphan*/  nn_fsm_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nn_fsm_isidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nn_fsm_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 
 scalar_t__ nn_slow (int) ; 
 int /*<<< orphan*/  nn_usock_init_from_fd (struct nn_usock*,int) ; 
 int /*<<< orphan*/  nn_worker_execute (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nn_usock_accept (struct nn_usock *self, struct nn_usock *listener)
{
    int s;

    /*  Start the actual accepting. */
    if (nn_fsm_isidle(&self->fsm)) {
        nn_fsm_start (&self->fsm);
        nn_fsm_action (&self->fsm, NN_USOCK_ACTION_BEING_ACCEPTED);
    }
    nn_fsm_action (&listener->fsm, NN_USOCK_ACTION_ACCEPT);

    /*  Try to accept new connection in synchronous manner. */
#if NN_HAVE_ACCEPT4
    s = accept4 (listener->s, NULL, NULL, SOCK_CLOEXEC);
    if ((s < 0) && (errno == ENOTSUP)) {
        /*  Apparently some old versions of Linux have a stub for this in libc,
            without any of the underlying kernel support. */
        s = accept (listener->s, NULL, NULL);
    }
#else
    s = accept (listener->s, NULL, NULL);
#endif

    /*  Immediate success. */
    if (nn_fast (s >= 0)) {
        /*  Disassociate the listener socket from the accepted
            socket. Is useful if we restart accepting on ACCEPT_ERROR  */
        listener->asock = NULL;
        self->asock = NULL;

        nn_usock_init_from_fd (self, s);
        nn_fsm_action (&listener->fsm, NN_USOCK_ACTION_DONE);
        nn_fsm_action (&self->fsm, NN_USOCK_ACTION_DONE);
        return;
    }

    /*  Detect a failure. Note that in ECONNABORTED case we simply ignore
        the error and wait for next connection in asynchronous manner. */
    errno_assert (errno == EAGAIN || errno == EWOULDBLOCK ||
        errno == ECONNABORTED || errno == ENFILE || errno == EMFILE ||
        errno == ENOBUFS || errno == ENOMEM);

    /*  Pair the two sockets.  They are already paired in case
        previous attempt failed on ACCEPT_ERROR  */
    nn_assert (!self->asock || self->asock == listener);
    self->asock = listener;
    nn_assert (!listener->asock || listener->asock == self);
    listener->asock = self;

    /*  Some errors are just ok to ignore for now.  We also stop repeating
        any errors until next IN_FD event so that we are not in a tight loop
        and allow processing other events in the meantime  */
    if (nn_slow (errno != EAGAIN && errno != EWOULDBLOCK
        && errno != ECONNABORTED && errno != listener->errnum))
    {
        listener->errnum = errno;
        listener->state = NN_USOCK_STATE_ACCEPTING_ERROR;
        nn_fsm_raise (&listener->fsm,
            &listener->event_error, NN_USOCK_ACCEPT_ERROR);
        return;
    }

    /*  Ask the worker thread to wait for the new connection. */
    nn_worker_execute (listener->worker, &listener->task_accept);
}