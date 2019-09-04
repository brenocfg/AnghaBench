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
typedef  int /*<<< orphan*/  bs ;

/* Variables and functions */
 int LARGE_SOCK_SIZE ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  error (char*,int) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

int sock_enlarge_out(int fd) {
    int ret, bs = LARGE_SOCK_SIZE;
    ret = setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &bs, sizeof(bs));

    if(ret == -1)
        error("Failed to set SO_SNDBUF on socket %d", fd);

    return ret;
}