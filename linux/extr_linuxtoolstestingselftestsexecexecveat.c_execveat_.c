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
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int execveat_(int fd, const char *path, char **argv, char **envp,
		     int flags)
{
#ifdef __NR_execveat
	return syscall(__NR_execveat, fd, path, argv, envp, flags);
#else
	errno = ENOSYS;
	return -1;
#endif
}