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
struct nn_usock {scalar_t__ state; int s; } ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 scalar_t__ NN_USOCK_STATE_BEING_ACCEPTED ; 
 scalar_t__ NN_USOCK_STATE_IDLE ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_NOSIGPIPE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void nn_usock_init_from_fd (struct nn_usock *self, int s)
{
    int rc;
    int opt;

    nn_assert (self->state == NN_USOCK_STATE_IDLE ||
        self->state == NN_USOCK_STATE_BEING_ACCEPTED);

    /*  Store the file descriptor. */
    nn_assert (self->s == -1);
    self->s = s;

    /* Setting FD_CLOEXEC option immediately after socket creation is the
        second best option after using SOCK_CLOEXEC. There is a race condition
        here (if process is forked between socket creation and setting
        the option) but the problem is pretty unlikely to happen. */
#if defined FD_CLOEXEC
    rc = fcntl (self->s, F_SETFD, FD_CLOEXEC);
#if defined NN_HAVE_OSX
    errno_assert (rc != -1 || errno == EINVAL);
#else
    errno_assert (rc != -1);
#endif
#endif

    /* If applicable, prevent SIGPIPE signal when writing to the connection
        already closed by the peer. */
#ifdef SO_NOSIGPIPE
    opt = 1;
    rc = setsockopt (self->s, SOL_SOCKET, SO_NOSIGPIPE, &opt, sizeof (opt));
#if defined NN_HAVE_OSX
    errno_assert (rc == 0 || errno == EINVAL);
#else
    errno_assert (rc == 0);
#endif
#endif

    /* Switch the socket to the non-blocking mode. All underlying sockets
        are always used in the callbackhronous mode. */
    opt = fcntl (self->s, F_GETFL, 0);
    if (opt == -1)
        opt = 0;
    if (!(opt & O_NONBLOCK)) {
        rc = fcntl (self->s, F_SETFL, opt | O_NONBLOCK);
#if defined NN_HAVE_OSX
        errno_assert (rc != -1 || errno == EINVAL);
#else
        errno_assert (rc != -1);
#endif
    }
}