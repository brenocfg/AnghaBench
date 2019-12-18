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
struct pollfd {int fd; int events; int revents; } ;
struct nn_pollfd {int events; int revents; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  fd ;

/* Variables and functions */
 int NN_POLLIN ; 
 int NN_POLLOUT ; 
 int /*<<< orphan*/  NN_RCVFD ; 
 int /*<<< orphan*/  NN_SNDFD ; 
 int /*<<< orphan*/  NN_SOL_SOCKET ; 
 int POLLIN ; 
 int /*<<< orphan*/  alloc_assert (struct pollfd*) ; 
 int errno ; 
 struct pollfd* nn_alloc (int,char*) ; 
 int /*<<< orphan*/  nn_assert (int) ; 
 int /*<<< orphan*/  nn_free (struct pollfd*) ; 
 int nn_getsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,size_t*) ; 
 scalar_t__ nn_slow (int) ; 
 int poll (struct pollfd*,int,int) ; 

int nn_poll (struct nn_pollfd *fds, int nfds, int timeout)
{
    int rc;
    int i;
    int pos;
    int fd;
    int res;
    size_t sz;
    struct pollfd *pfd;

    /*  Construct a pollset to be used with OS-level 'poll' function. */
    pfd = nn_alloc (sizeof (struct pollfd) * nfds * 2, "pollset");
    alloc_assert (pfd);
    pos = 0;
    for (i = 0; i != nfds; ++i) {
        if (fds [i].events & NN_POLLIN) {
            sz = sizeof (fd);
            rc = nn_getsockopt (fds [i].fd, NN_SOL_SOCKET, NN_RCVFD, &fd, &sz);
            if (nn_slow (rc < 0)) {
                nn_free (pfd);
                return -1;
            }
            nn_assert (sz == sizeof (fd));
            pfd [pos].fd = fd;
            pfd [pos].events = POLLIN;
            ++pos;
        }
        if (fds [i].events & NN_POLLOUT) {
            sz = sizeof (fd);
            rc = nn_getsockopt (fds [i].fd, NN_SOL_SOCKET, NN_SNDFD, &fd, &sz);
            if (nn_slow (rc < 0)) {
                nn_free (pfd);
                return -1;
            }
            nn_assert (sz == sizeof (fd));
            pfd [pos].fd = fd;
            pfd [pos].events = POLLIN;
            ++pos;
        }
    }    

    /*  Do the polling itself. */
    rc = poll (pfd, pos, timeout);
    if (nn_slow (rc <= 0)) {
        res = errno;
        nn_free (pfd);
        errno = res;
        return rc;
    }

    /*  Move the results from OS-level poll to nn_poll's pollset. */
    res = 0;
    pos = 0;
    for (i = 0; i != nfds; ++i) {
        fds [i].revents = 0;
        if (fds [i].events & NN_POLLIN) {
            if (pfd [pos].revents & POLLIN)
                fds [i].revents |= NN_POLLIN;
            ++pos;
        }
        if (fds [i].events & NN_POLLOUT) {
            if (pfd [pos].revents & POLLIN)
                fds [i].revents |= NN_POLLOUT;
            ++pos;
        }
        if (fds [i].revents)
            ++res;
    }

    nn_free (pfd);
    return res;
}