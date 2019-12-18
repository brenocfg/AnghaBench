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
typedef  int time_t ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int CHILD_THREAD_MIN_WAIT ; 
 int /*<<< orphan*/  CLONE_PIDFD ; 
 int /*<<< orphan*/  child_poll_exec_test ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int getpid () ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,char const*,...) ; 
 int /*<<< orphan*/  ksft_print_msg (char*,...) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char*,char const*) ; 
 int pidfd_clone (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_pidfd (char const*,int) ; 
 int time (int /*<<< orphan*/ *) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_pidfd_poll_exec(int use_waitpid)
{
	int pid, pidfd = 0;
	int status, ret;
	pthread_t t1;
	time_t prog_start = time(NULL);
	const char *test_name = "pidfd_poll check for premature notification on child thread exec";

	ksft_print_msg("Parent: pid: %d\n", getpid());
	pid = pidfd_clone(CLONE_PIDFD, &pidfd, child_poll_exec_test);
	if (pid < 0)
		ksft_exit_fail_msg("%s test: pidfd_clone failed (ret %d, errno %d)\n",
				   test_name, pid, errno);

	ksft_print_msg("Parent: Waiting for Child (%d) to complete.\n", pid);

	if (use_waitpid) {
		ret = waitpid(pid, &status, 0);
		if (ret == -1)
			ksft_print_msg("Parent: error\n");

		if (ret == pid)
			ksft_print_msg("Parent: Child process waited for.\n");
	} else {
		poll_pidfd(test_name, pidfd);
	}

	time_t prog_time = time(NULL) - prog_start;

	ksft_print_msg("Time waited for child: %lu\n", prog_time);

	close(pidfd);

	if (prog_time < CHILD_THREAD_MIN_WAIT || prog_time > CHILD_THREAD_MIN_WAIT + 2)
		ksft_exit_fail_msg("%s test: Failed\n", test_name);
	else
		ksft_test_result_pass("%s test: Passed\n", test_name);
}