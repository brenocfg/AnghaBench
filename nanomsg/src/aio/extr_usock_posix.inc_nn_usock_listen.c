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
struct nn_usock {int /*<<< orphan*/  fsm; int /*<<< orphan*/  s; } ;

/* Variables and functions */
 int /*<<< orphan*/  NN_USOCK_ACTION_LISTEN ; 
 int /*<<< orphan*/  NN_USOCK_STATE_STARTING ; 
 int errno ; 
 int listen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_assert_state (struct nn_usock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nn_fsm_action (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nn_slow (int) ; 

int nn_usock_listen (struct nn_usock *self, int backlog)
{
    int rc;

    /*  You can start listening only before the socket is connected. */
    nn_assert_state (self, NN_USOCK_STATE_STARTING);

    /*  Start listening for incoming connections. */
    rc = listen (self->s, backlog);
    if (nn_slow (rc != 0))
        return -errno;

    /*  Notify the state machine. */
    nn_fsm_action (&self->fsm, NN_USOCK_ACTION_LISTEN);

    return 0;
}