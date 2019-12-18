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
struct nn_usock {int /*<<< orphan*/  fsm; } ;

/* Variables and functions */
 int SOCK_CLOEXEC ; 
 int errno ; 
 int /*<<< orphan*/  nn_fsm_start (int /*<<< orphan*/ *) ; 
 scalar_t__ nn_slow (int) ; 
 int /*<<< orphan*/  nn_usock_init_from_fd (struct nn_usock*,int) ; 
 int socket (int,int,int) ; 

int nn_usock_start (struct nn_usock *self, int domain, int type, int protocol)
{
    int s;

    /*  If the operating system allows to directly open the socket with CLOEXEC
        flag, do so. That way there are no race conditions. */
#ifdef SOCK_CLOEXEC
    type |= SOCK_CLOEXEC;
#endif

    /* Open the underlying socket. */
    s = socket (domain, type, protocol);
    if (nn_slow (s < 0))
       return -errno;

    nn_usock_init_from_fd (self, s);

    /*  Start the state machine. */
    nn_fsm_start (&self->fsm);

    return 0;
}