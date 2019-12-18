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
struct nn_device_recipe {int dummy; } ;
typedef  int /*<<< orphan*/  op ;

/* Variables and functions */
 int AF_SP_RAW ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  NN_DOMAIN ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int nn_device_mvmsg (struct nn_device_recipe*,int,int,int /*<<< orphan*/ ) ; 
 int nn_getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 scalar_t__ nn_slow (int) ; 

int nn_device_loopback (struct nn_device_recipe *device, int s)
{
    int rc;
    int op;
    size_t opsz;

    /*  Check whether the socket is a "raw" socket. */
    opsz = sizeof (op);
    rc = nn_getsockopt (s, NN_SOL_SOCKET, NN_DOMAIN, &op, &opsz);
    if (nn_slow (rc != 0))
        return -1;
    nn_assert (opsz == sizeof (op));
    if (op != AF_SP_RAW) {
        errno = EINVAL;
        return -1;
    }

    for (;;) {
        rc = nn_device_mvmsg (device, s, s, 0);
        if (nn_slow (rc < 0))
            return -1;
    }
}