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

int sock_setreuse_port(int fd, int reuse) {
    int ret;

#ifdef SO_REUSEPORT
    ret = setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse));
    if(ret == -1 && errno != ENOPROTOOPT)
        error("failed to set SO_REUSEPORT on socket %d", fd);
#else
    ret = -1;
#endif

    return ret;
}