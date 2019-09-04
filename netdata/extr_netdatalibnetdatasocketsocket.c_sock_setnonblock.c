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
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 

int sock_setnonblock(int fd) {
    int flags;

    flags = fcntl(fd, F_GETFL);
    flags |= O_NONBLOCK;

    int ret = fcntl(fd, F_SETFL, flags);
    if(ret < 0)
        error("Failed to set O_NONBLOCK on socket %d", fd);

    return ret;
}