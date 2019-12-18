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
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  CLONE_NEWNET ; 
 scalar_t__ ENOSYS ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  S ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
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
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
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
	if (unshare(CLONE_NEWNET) == -1) {
		if (errno == ENOSYS || errno == EPERM) {
			return 4;
		}
		return 1;
	}
	/* Distinguisher between two otherwise empty net namespaces. */
	if (socket(AF_UNIX, SOCK_STREAM, 0) == -1) {
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
		if (unshare(CLONE_NEWNET) == -1) {
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
		snprintf(buf, sizeof(buf), "/proc/%u/ns/net", pid);
		nsfd = open(buf, O_RDONLY);
		if (nsfd == -1) {
			return 1;
		}
	}

	/* Reliably pin dentry into dcache. */
	(void)open("/proc/net/unix", O_RDONLY);

	if (setns(nsfd, CLONE_NEWNET) == -1) {
		return 1;
	}

	kill(pid, SIGTERM);
	pid = 0;

	{
		char buf[4096];
		ssize_t rv;
		int fd;

		fd = open("/proc/net/unix", O_RDONLY);
		if (fd == -1) {
			return 1;
		}

#define S "Num       RefCount Protocol Flags    Type St Inode Path\n"
		rv = read(fd, buf, sizeof(buf));

		assert(rv == strlen(S));
		assert(memcmp(buf, S, strlen(S)) == 0);
	}

	return 0;
}