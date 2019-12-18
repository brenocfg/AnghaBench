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
struct stat {scalar_t__ st_ino; } ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int CLONE_NEWUSER ; 
 int CLONE_NEWUTS ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  NS_GET_USERNS ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PR_SET_PDEATHSIG ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ fork () ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int ioctl (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pipe (int*) ; 
 int pr_err (char*,...) ; 
 int /*<<< orphan*/  prctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,char*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 scalar_t__ unshare (int) ; 
 int /*<<< orphan*/  wait (int /*<<< orphan*/ *) ; 

int main(int argc, char *argvp[])
{
	int pfd[2], ns, uns, init_uns;
	struct stat st1, st2;
	char path[128];
	pid_t pid;
	char c;

	if (pipe(pfd))
		return 1;

	pid = fork();
	if (pid < 0)
		return pr_err("fork");
	if (pid == 0) {
		prctl(PR_SET_PDEATHSIG, SIGKILL);
		if (unshare(CLONE_NEWUTS | CLONE_NEWUSER))
			return pr_err("unshare");
		close(pfd[0]);
		close(pfd[1]);
		while (1)
			sleep(1);
		return 0;
	}
	close(pfd[1]);
	if (read(pfd[0], &c, 1) != 0)
		return pr_err("Unable to read from pipe");
	close(pfd[0]);

	snprintf(path, sizeof(path), "/proc/%d/ns/uts", pid);
	ns = open(path, O_RDONLY);
	if (ns < 0)
		return pr_err("Unable to open %s", path);

	uns = ioctl(ns, NS_GET_USERNS);
	if (uns < 0)
		return pr_err("Unable to get an owning user namespace");

	if (fstat(uns, &st1))
		return pr_err("fstat");

	snprintf(path, sizeof(path), "/proc/%d/ns/user", pid);
	if (stat(path, &st2))
		return pr_err("stat");

	if (st1.st_ino != st2.st_ino)
		return pr_err("NS_GET_USERNS returned a wrong namespace");

	init_uns = ioctl(uns, NS_GET_USERNS);
	if (uns < 0)
		return pr_err("Unable to get an owning user namespace");

	if (ioctl(init_uns, NS_GET_USERNS) >= 0 || errno != EPERM)
		return pr_err("Don't get EPERM");

	if (unshare(CLONE_NEWUSER))
		return pr_err("unshare");

	if (ioctl(ns, NS_GET_USERNS) >= 0 || errno != EPERM)
		return pr_err("Don't get EPERM");
	if (ioctl(init_uns, NS_GET_USERNS) >= 0 || errno != EPERM)
		return pr_err("Don't get EPERM");

	kill(pid, SIGKILL);
	wait(NULL);
	return 0;
}