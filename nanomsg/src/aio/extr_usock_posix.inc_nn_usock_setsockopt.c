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
struct nn_usock {scalar_t__ state; int /*<<< orphan*/  s; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NN_USOCK_STATE_ACCEPTED ; 
 scalar_t__ NN_USOCK_STATE_STARTING ; 
 int errno ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 scalar_t__ nn_slow (int) ; 
 int setsockopt (int /*<<< orphan*/ ,int,int,void const*,int /*<<< orphan*/ ) ; 

int nn_usock_setsockopt (struct nn_usock *self, int level, int optname,
    const void *optval, size_t optlen)
{
    int rc;

    /*  The socket can be modified only before it's active. */
    nn_assert (self->state == NN_USOCK_STATE_STARTING ||
        self->state == NN_USOCK_STATE_ACCEPTED);

    /*  EINVAL errors are ignored on OSX platform. The reason for that is buggy
        OSX behaviour where setsockopt returns EINVAL if the peer have already
        disconnected. Thus, nn_usock_setsockopt() can succeed on OSX even though
        the option value was invalid, but the peer have already closed the
        connection. This behaviour should be relatively harmless. */
    rc = setsockopt (self->s, level, optname, optval, (socklen_t) optlen);
#if defined NN_HAVE_OSX
    if (nn_slow (rc != 0 && errno != EINVAL))
        return -errno;
#else
    if (nn_slow (rc != 0))
        return -errno;
#endif

    return 0;
}