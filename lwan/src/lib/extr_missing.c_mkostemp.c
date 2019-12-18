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
 int /*<<< orphan*/  F_SETFD ; 
 int O_CLOEXEC ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,...) ; 
 int mkstemp (char*) ; 

int mkostemp(char *tmpl, int flags)
{
    int fd, fl;

    fd = mkstemp(tmpl);
    if (fd < 0)
        return -1;

    fl = fcntl(fd, F_GETFD);
    if (fl < 0)
        goto out;

    if (flags & O_CLOEXEC)
        fl |= FD_CLOEXEC;

    if (fcntl(fd, F_SETFD, fl) < 0)
        goto out;

    return fd;

out:
    close(fd);
    return -1;
}