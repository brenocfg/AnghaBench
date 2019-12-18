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

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int recv (int,void*,size_t,int) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

__attribute__((used)) static int sock_recv(int fd, void *msg, size_t len, int flags)
{
    int ret;
    do
    {
        if ((ret = recv(fd, msg, len, flags)) == -1) WARN("recv error %s\n", strerror(errno));
    }
    while(ret == -1 && errno == EINTR);
    return ret;
}