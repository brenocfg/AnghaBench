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
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  lwan_status_critical_perror (char*) ; 

__attribute__((used)) static int set_socket_flags(int fd)
{
    int flags = fcntl(fd, F_GETFD);
    if (flags < 0)
        lwan_status_critical_perror("Could not obtain socket flags");
    if (fcntl(fd, F_SETFD, flags | FD_CLOEXEC) < 0)
        lwan_status_critical_perror("Could not set socket flags");

    flags = fcntl(fd, F_GETFL);
    if (flags < 0)
        lwan_status_critical_perror("Could not obtain socket flags");
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
        lwan_status_critical_perror("Could not set socket flags");

    return fd;
}