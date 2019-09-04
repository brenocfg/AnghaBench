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
struct pollfd {int fd; int events; int /*<<< orphan*/  revents; } ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int POLLOUT ; 
 scalar_t__ errno ; 
 int poll (struct pollfd*,int,int) ; 
 int send (int,void*,size_t,int) ; 

ssize_t send_timeout(int sockfd, void *buf, size_t len, int flags, int timeout) {
    for(;;) {
        struct pollfd fd = {
                .fd = sockfd,
                .events = POLLOUT,
                .revents = 0
        };

        errno = 0;
        int retval = poll(&fd, 1, timeout * 1000);

        if(retval == -1) {
            // failed

            if(errno == EINTR || errno == EAGAIN)
                continue;

            return -1;
        }

        if(!retval) {
            // timeout
            return 0;
        }

        if(fd.events & POLLOUT) break;
    }

    return send(sockfd, buf, len, flags);
}