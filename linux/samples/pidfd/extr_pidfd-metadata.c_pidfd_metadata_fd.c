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
typedef  int pid_t ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
#define  EPERM 128 
 int O_CLOEXEC ; 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int sys_pidfd_send_signal (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*,...) ; 

__attribute__((used)) static int pidfd_metadata_fd(pid_t pid, int pidfd)
{
	int procfd, ret;
	char path[100];

	snprintf(path, sizeof(path), "/proc/%d", pid);
	procfd = open(path, O_DIRECTORY | O_RDONLY | O_CLOEXEC);
	if (procfd < 0) {
		warn("Failed to open %s\n", path);
		return -1;
	}

	/*
	 * Verify that the pid has not been recycled and our /proc/<pid> handle
	 * is still valid.
	 */
	ret = sys_pidfd_send_signal(pidfd, 0, NULL, 0);
	if (ret < 0) {
		switch (errno) {
		case EPERM:
			/* Process exists, just not allowed to signal it. */
			break;
		default:
			warn("Failed to signal process\n");
			close(procfd);
			procfd = -1;
		}
	}

	return procfd;
}