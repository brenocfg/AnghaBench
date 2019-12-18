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
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int O_CLOEXEC ; 
 int O_DIRECTORY ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,char const*,...) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char*,char const*) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,scalar_t__) ; 
 int sys_pidfd_send_signal (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_pid (scalar_t__) ; 

__attribute__((used)) static int test_pidfd_send_signal_exited_fail(void)
{
	int pidfd, ret, saved_errno;
	char buf[256];
	pid_t pid;
	const char *test_name = "pidfd_send_signal signal exited process";

	pid = fork();
	if (pid < 0)
		ksft_exit_fail_msg("%s test: Failed to create new process\n",
				   test_name);

	if (pid == 0)
		_exit(EXIT_SUCCESS);

	snprintf(buf, sizeof(buf), "/proc/%d", pid);

	pidfd = open(buf, O_DIRECTORY | O_CLOEXEC);

	(void)wait_for_pid(pid);

	if (pidfd < 0)
		ksft_exit_fail_msg(
			"%s test: Failed to open process file descriptor\n",
			test_name);

	ret = sys_pidfd_send_signal(pidfd, 0, NULL, 0);
	saved_errno = errno;
	close(pidfd);
	if (ret == 0)
		ksft_exit_fail_msg(
			"%s test: Managed to send signal to process even though it should have failed\n",
			test_name);

	if (saved_errno != ESRCH)
		ksft_exit_fail_msg(
			"%s test: Expected to receive ESRCH as errno value but received %d instead\n",
			test_name, saved_errno);

	ksft_test_result_pass("%s test: Failed to send signal as expected\n",
			      test_name);
	return 0;
}