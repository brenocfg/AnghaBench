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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CLONE_NEWIPC ; 
 scalar_t__ ENOSYS ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  IPC_CREAT ; 
 int /*<<< orphan*/  IPC_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  S32 ; 
 int /*<<< orphan*/  S64 ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  f ; 
 int fork () ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause () ; 
 int pid ; 
 int pipe (int*) ; 
 int read (int,char*,int) ; 
 int setns (int,int /*<<< orphan*/ ) ; 
 int shmget (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int unshare (int /*<<< orphan*/ ) ; 
 int write (int,char*,int) ; 

int main(void)
{
	int fd[2];
	char _ = 0;
	int nsfd;

	atexit(f);

	/* Check for priviledges and syscall availability straight away. */
	if (unshare(CLONE_NEWIPC) == -1) {
		if (errno == ENOSYS || errno == EPERM) {
			return 4;
		}
		return 1;
	}
	/* Distinguisher between two otherwise empty IPC namespaces. */
	if (shmget(IPC_PRIVATE, 1, IPC_CREAT) == -1) {
		return 1;
	}

	if (pipe(fd) == -1) {
		return 1;
	}

	pid = fork();
	if (pid == -1) {
		return 1;
	}

	if (pid == 0) {
		if (unshare(CLONE_NEWIPC) == -1) {
			return 1;
		}

		if (write(fd[1], &_, 1) != 1) {
			return 1;
		}

		pause();

		return 0;
	}

	if (read(fd[0], &_, 1) != 1) {
		return 1;
	}

	{
		char buf[64];
		snprintf(buf, sizeof(buf), "/proc/%u/ns/ipc", pid);
		nsfd = open(buf, O_RDONLY);
		if (nsfd == -1) {
			return 1;
		}
	}

	/* Reliably pin dentry into dcache. */
	(void)open("/proc/sysvipc/shm", O_RDONLY);

	if (setns(nsfd, CLONE_NEWIPC) == -1) {
		return 1;
	}

	kill(pid, SIGTERM);
	pid = 0;

	{
		char buf[4096];
		ssize_t rv;
		int fd;

		fd = open("/proc/sysvipc/shm", O_RDONLY);
		if (fd == -1) {
			return 1;
		}

#define S32 "       key      shmid perms       size  cpid  lpid nattch   uid   gid  cuid  cgid      atime      dtime      ctime        rss       swap\n"
#define S64 "       key      shmid perms                  size  cpid  lpid nattch   uid   gid  cuid  cgid      atime      dtime      ctime                   rss                  swap\n"
		rv = read(fd, buf, sizeof(buf));
		if (rv == strlen(S32)) {
			assert(memcmp(buf, S32, strlen(S32)) == 0);
		} else if (rv == strlen(S64)) {
			assert(memcmp(buf, S64, strlen(S64)) == 0);
		} else {
			assert(0);
		}
	}

	return 0;
}