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
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int) ; 
 int pipe (int*) ; 

int pipe2(int pipefd[2], int flags)
{
    int r;

    r = pipe(pipefd);
    if (r < 0)
        return r;

    if (fcntl(pipefd[0], F_SETFL, flags) < 0 ||
        fcntl(pipefd[1], F_SETFL, flags) < 0) {
        int saved_errno = errno;

        close(pipefd[0]);
        close(pipefd[1]);

        errno = saved_errno;
        return -1;
    }

    return 0;
}