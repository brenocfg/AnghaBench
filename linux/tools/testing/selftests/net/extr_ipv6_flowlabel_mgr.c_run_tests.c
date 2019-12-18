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

/* Variables and functions */
 int FL_MIN_LINGER ; 
 int IPV6_FL_F_CREATE ; 
 int IPV6_FL_F_EXCL ; 
 int /*<<< orphan*/  IPV6_FL_S_ANY ; 
 int /*<<< orphan*/  IPV6_FL_S_EXCL ; 
 int /*<<< orphan*/  IPV6_FL_S_PROCESS ; 
 int /*<<< orphan*/  IPV6_FL_S_USER ; 
 int /*<<< orphan*/  USHRT_MAX ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 scalar_t__ cfg_long_running ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  explain (char*) ; 
 int /*<<< orphan*/  flowlabel_get (int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flowlabel_put (int,int) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ setuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 int wait (int*) ; 

__attribute__((used)) static void run_tests(int fd)
{
	int wstatus;
	pid_t pid;

	explain("cannot get non-existent label");
	expect_fail(flowlabel_get(fd, 1, IPV6_FL_S_ANY, 0));

	explain("cannot put non-existent label");
	expect_fail(flowlabel_put(fd, 1));

	explain("cannot create label greater than 20 bits");
	expect_fail(flowlabel_get(fd, 0x1FFFFF, IPV6_FL_S_ANY,
				  IPV6_FL_F_CREATE));

	explain("create a new label (FL_F_CREATE)");
	expect_pass(flowlabel_get(fd, 1, IPV6_FL_S_ANY, IPV6_FL_F_CREATE));
	explain("can get the label (without FL_F_CREATE)");
	expect_pass(flowlabel_get(fd, 1, IPV6_FL_S_ANY, 0));
	explain("can get it again with create flag set, too");
	expect_pass(flowlabel_get(fd, 1, IPV6_FL_S_ANY, IPV6_FL_F_CREATE));
	explain("cannot get it again with the exclusive (FL_FL_EXCL) flag");
	expect_fail(flowlabel_get(fd, 1, IPV6_FL_S_ANY,
					 IPV6_FL_F_CREATE | IPV6_FL_F_EXCL));
	explain("can now put exactly three references");
	expect_pass(flowlabel_put(fd, 1));
	expect_pass(flowlabel_put(fd, 1));
	expect_pass(flowlabel_put(fd, 1));
	expect_fail(flowlabel_put(fd, 1));

	explain("create a new exclusive label (FL_S_EXCL)");
	expect_pass(flowlabel_get(fd, 2, IPV6_FL_S_EXCL, IPV6_FL_F_CREATE));
	explain("cannot get it again in non-exclusive mode");
	expect_fail(flowlabel_get(fd, 2, IPV6_FL_S_ANY,  IPV6_FL_F_CREATE));
	explain("cannot get it again in exclusive mode either");
	expect_fail(flowlabel_get(fd, 2, IPV6_FL_S_EXCL, IPV6_FL_F_CREATE));
	expect_pass(flowlabel_put(fd, 2));

	if (cfg_long_running) {
		explain("cannot reuse the label, due to linger");
		expect_fail(flowlabel_get(fd, 2, IPV6_FL_S_ANY,
					  IPV6_FL_F_CREATE));
		explain("after sleep, can reuse");
		sleep(FL_MIN_LINGER * 2 + 1);
		expect_pass(flowlabel_get(fd, 2, IPV6_FL_S_ANY,
					  IPV6_FL_F_CREATE));
	}

	explain("create a new user-private label (FL_S_USER)");
	expect_pass(flowlabel_get(fd, 3, IPV6_FL_S_USER, IPV6_FL_F_CREATE));
	explain("cannot get it again in non-exclusive mode");
	expect_fail(flowlabel_get(fd, 3, IPV6_FL_S_ANY, 0));
	explain("cannot get it again in exclusive mode");
	expect_fail(flowlabel_get(fd, 3, IPV6_FL_S_EXCL, 0));
	explain("can get it again in user mode");
	expect_pass(flowlabel_get(fd, 3, IPV6_FL_S_USER, 0));
	explain("child process can get it too, but not after setuid(nobody)");
	pid = fork();
	if (pid == -1)
		error(1, errno, "fork");
	if (!pid) {
		expect_pass(flowlabel_get(fd, 3, IPV6_FL_S_USER, 0));
		if (setuid(USHRT_MAX))
			fprintf(stderr, "[INFO] skip setuid child test\n");
		else
			expect_fail(flowlabel_get(fd, 3, IPV6_FL_S_USER, 0));
		exit(0);
	}
	if (wait(&wstatus) == -1)
		error(1, errno, "wait");
	if (!WIFEXITED(wstatus) || WEXITSTATUS(wstatus) != 0)
		error(1, errno, "wait: unexpected child result");

	explain("create a new process-private label (FL_S_PROCESS)");
	expect_pass(flowlabel_get(fd, 4, IPV6_FL_S_PROCESS, IPV6_FL_F_CREATE));
	explain("can get it again");
	expect_pass(flowlabel_get(fd, 4, IPV6_FL_S_PROCESS, 0));
	explain("child process cannot can get it");
	pid = fork();
	if (pid == -1)
		error(1, errno, "fork");
	if (!pid) {
		expect_fail(flowlabel_get(fd, 4, IPV6_FL_S_PROCESS, 0));
		exit(0);
	}
	if (wait(&wstatus) == -1)
		error(1, errno, "wait");
	if (!WIFEXITED(wstatus) || WEXITSTATUS(wstatus) != 0)
		error(1, errno, "wait: unexpected child result");
}