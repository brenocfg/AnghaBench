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
struct sockaddr {int dummy; } ;
struct nn_usock {int /*<<< orphan*/  task_connecting; int /*<<< orphan*/  worker; int /*<<< orphan*/  fsm; scalar_t__ errnum; int /*<<< orphan*/  s; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ EINPROGRESS ; 
 int /*<<< orphan*/  NN_USOCK_ACTION_CONNECT ; 
 int /*<<< orphan*/  NN_USOCK_ACTION_DONE ; 
 int /*<<< orphan*/  NN_USOCK_ACTION_ERROR ; 
 int connect (int /*<<< orphan*/ ,struct sockaddr const*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ nn_fast (int) ; 
 int /*<<< orphan*/  nn_fsm_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nn_slow (int) ; 
 int /*<<< orphan*/  nn_worker_execute (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void nn_usock_connect (struct nn_usock *self, const struct sockaddr *addr,
    size_t addrlen)
{
    int rc;

    /*  Notify the state machine that we've started connecting. */
    nn_fsm_action (&self->fsm, NN_USOCK_ACTION_CONNECT);

    /* Do the connect itself. */
    rc = connect (self->s, addr, (socklen_t) addrlen);

    /* Immediate success. */
    if (nn_fast (rc == 0)) {
        nn_fsm_action (&self->fsm, NN_USOCK_ACTION_DONE);
        return;
    }

    /*  Immediate error. */
    if (nn_slow (errno != EINPROGRESS)) {
        self->errnum = errno;
        nn_fsm_action (&self->fsm, NN_USOCK_ACTION_ERROR);
        return;
    }

    /*  Start asynchronous connect. */
    nn_worker_execute (self->worker, &self->task_connecting);
}