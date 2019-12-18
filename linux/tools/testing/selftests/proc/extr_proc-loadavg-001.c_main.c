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
typedef  int ssize_t ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE_NEWPID ; 
 scalar_t__ ENOSYS ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ errno ; 
 int fork () ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,char*,int) ; 
 int unshare (int /*<<< orphan*/ ) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

int main(void)
{
	pid_t pid;
	int wstatus;

	if (unshare(CLONE_NEWPID) == -1) {
		if (errno == ENOSYS || errno == EPERM)
			return 4;
		return 1;
	}

	pid = fork();
	if (pid == -1)
		return 1;
	if (pid == 0) {
		char buf[128], *p;
		int fd;
		ssize_t rv;

		fd = open("/proc/loadavg" , O_RDONLY);
		if (fd == -1)
			return 1;
		rv = read(fd, buf, sizeof(buf));
		if (rv < 3)
			return 1;
		p = buf + rv;

		/* pid 1 */
		if (!(p[-3] == ' ' && p[-2] == '1' && p[-1] == '\n'))
			return 1;

		pid = fork();
		if (pid == -1)
			return 1;
		if (pid == 0)
			return 0;
		if (waitpid(pid, NULL, 0) == -1)
			return 1;

		lseek(fd, 0, SEEK_SET);
		rv = read(fd, buf, sizeof(buf));
		if (rv < 3)
			return 1;
		p = buf + rv;

		/* pid 2 */
		if (!(p[-3] == ' ' && p[-2] == '2' && p[-1] == '\n'))
			return 1;

		return 0;
	}

	if (waitpid(pid, &wstatus, 0) == -1)
		return 1;
	if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 0)
		return 0;
	return 1;
}