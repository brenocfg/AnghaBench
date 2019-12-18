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
struct timeval {int tv_sec; int tv_usec; } ;
typedef  int /*<<< orphan*/  sndfd ;
typedef  int /*<<< orphan*/  rcvfd ;
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  SOCKET ;

/* Variables and functions */
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int NN_IN ; 
 int NN_OUT ; 
 int /*<<< orphan*/  NN_RCVFD ; 
 int /*<<< orphan*/  NN_SNDFD ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int SOCKET_ERROR ; 
 int /*<<< orphan*/  errno_assert (int) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int nn_getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  wsa_assert (int) ; 

int getevents (int s, int events, int timeout)
{
    int rc;
    fd_set pollset;
#if defined NN_HAVE_WINDOWS
    SOCKET rcvfd;
    SOCKET sndfd;
#else
    int rcvfd;
    int sndfd;
    int maxfd;
#endif
    size_t fdsz;
    struct timeval tv;
    int revents;

#if !defined NN_HAVE_WINDOWS
    maxfd = 0;
#endif
    FD_ZERO (&pollset);

    if (events & NN_IN) {
        fdsz = sizeof (rcvfd);
        rc = nn_getsockopt (s, NN_SOL_SOCKET, NN_RCVFD, (char*) &rcvfd, &fdsz);
        errno_assert (rc == 0);
        nn_assert (fdsz == sizeof (rcvfd));
        FD_SET (rcvfd, &pollset);
#if !defined NN_HAVE_WINDOWS
        if (rcvfd + 1 > maxfd)
            maxfd = rcvfd + 1;
#endif
    }

    if (events & NN_OUT) {
        fdsz = sizeof (sndfd);
        rc = nn_getsockopt (s, NN_SOL_SOCKET, NN_SNDFD, (char*) &sndfd, &fdsz);
        errno_assert (rc == 0);
        nn_assert (fdsz == sizeof (sndfd));
        FD_SET (sndfd, &pollset);
#if !defined NN_HAVE_WINDOWS
        if (sndfd + 1 > maxfd)
            maxfd = sndfd + 1;
#endif
    }

    if (timeout >= 0) {
        tv.tv_sec = timeout / 1000;
        tv.tv_usec = (timeout % 1000) * 1000;
    }
#if defined NN_HAVE_WINDOWS
    rc = select (0, &pollset, NULL, NULL, timeout < 0 ? NULL : &tv);
    wsa_assert (rc != SOCKET_ERROR);
#else
    rc = select (maxfd, &pollset, NULL, NULL, timeout < 0 ? NULL : &tv);
    errno_assert (rc >= 0);
#endif
    revents = 0;
    if ((events & NN_IN) && FD_ISSET (rcvfd, &pollset))
        revents |= NN_IN;
    if ((events & NN_OUT) && FD_ISSET (sndfd, &pollset))
        revents |= NN_OUT;
    return revents;
}