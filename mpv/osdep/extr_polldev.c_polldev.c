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
struct pollfd {int fd; int events; int revents; } ;
typedef  size_t nfds_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int POLLERR ; 
 int POLLIN ; 
 int POLLOUT ; 
 int poll (struct pollfd*,size_t,int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

int polldev(struct pollfd fds[], nfds_t nfds, int timeout) {
#ifdef __APPLE__
    int maxfd = 0;
    fd_set readfds, writefds, errorfds;
    FD_ZERO(&readfds);
    FD_ZERO(&writefds);
    FD_ZERO(&errorfds);
    for (size_t i = 0; i < nfds; ++i) {
        struct pollfd *fd = &fds[i];
        if (fd->fd > maxfd) {
            maxfd = fd->fd;
        }
        if ((fd->events & POLLIN)) {
            FD_SET(fd->fd, &readfds);
        }
        if ((fd->events & POLLOUT)) {
            FD_SET(fd->fd, &writefds);
        }
        if ((fd->events & POLLERR)) {
            FD_SET(fd->fd, &errorfds);
        }
    }
    struct timeval _timeout = {
        .tv_sec = timeout / 1000,
        .tv_usec = (timeout % 1000) * 1000
    };
    int n = select(maxfd + 1, &readfds, &writefds, &errorfds,
        timeout != -1 ? &_timeout : NULL);
    if (n < 0) {
        return n;
    }
    for (size_t i = 0; i < nfds; ++i) {
        struct pollfd *fd = &fds[i];
        fd->revents = 0;
        if (FD_ISSET(fd->fd, &readfds)) {
            fd->revents |= POLLIN;
        }
        if (FD_ISSET(fd->fd, &writefds)) {
            fd->revents |= POLLOUT;
        }
        if (FD_ISSET(fd->fd, &errorfds)) {
            fd->revents |= POLLERR;
        }
    }
    return n;
#else
    return poll(fds, nfds, timeout);
#endif
}