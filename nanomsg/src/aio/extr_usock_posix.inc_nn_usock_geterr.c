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
struct nn_usock {int /*<<< orphan*/  s; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  opt ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ERROR ; 
 int errno ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  nn_assert (int) ; 

__attribute__((used)) static int nn_usock_geterr (struct nn_usock *self)
{
    int rc;
    int opt;
#if defined NN_HAVE_HPUX
    int optsz;
#else
    socklen_t optsz;
#endif

    opt = 0;
    optsz = sizeof (opt);
    rc = getsockopt (self->s, SOL_SOCKET, SO_ERROR, &opt, &optsz);

    /*  The following should handle both Solaris and UNIXes derived from BSD. */
    if (rc == -1)
        return errno;
    errno_assert (rc == 0);
    nn_assert (optsz == sizeof (opt));
    return opt;
}