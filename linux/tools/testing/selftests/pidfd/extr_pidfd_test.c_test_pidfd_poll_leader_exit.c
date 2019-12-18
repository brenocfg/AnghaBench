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

/* Variables and functions */
 int CHILD_THREAD_MIN_WAIT ; 
 int /*<<< orphan*/  CLONE_PIDFD ; 
 int MAP_ANONYMOUS ; 
 int* MAP_FAILED ; 
 int MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int* child_exit_secs ; 
 int /*<<< orphan*/  child_poll_leader_exit_test ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int getpid () ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,char const*,...) ; 
 int /*<<< orphan*/  ksft_print_msg (char*,...) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char*,char const*) ; 
 int* mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int pidfd_clone (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  poll_pidfd (char const*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int time (int /*<<< orphan*/ *) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_pidfd_poll_leader_exit(int use_waitpid)
{
	int pid, pidfd = 0;
	int status, ret;
	time_t prog_start = time(NULL);
	const char *test_name = "pidfd_poll check for premature notification on non-empty"
				"group leader exit";

	child_exit_secs = mmap(NULL, sizeof *child_exit_secs, PROT_READ | PROT_WRITE,
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	if (child_exit_secs == MAP_FAILED)
		ksft_exit_fail_msg("%s test: mmap failed (errno %d)\n",
				   test_name, errno);

	ksft_print_msg("Parent: pid: %d\n", getpid());
	pid = pidfd_clone(CLONE_PIDFD, &pidfd, child_poll_leader_exit_test);
	if (pid < 0)
		ksft_exit_fail_msg("%s test: pidfd_clone failed (ret %d, errno %d)\n",
				   test_name, pid, errno);

	ksft_print_msg("Parent: Waiting for Child (%d) to complete.\n", pid);

	if (use_waitpid) {
		ret = waitpid(pid, &status, 0);
		if (ret == -1)
			ksft_print_msg("Parent: error\n");
	} else {
		/*
		 * This sleep tests for the case where if the child exits, and is in
		 * EXIT_ZOMBIE, but the thread group leader is non-empty, then the poll
		 * doesn't prematurely return even though there are active threads
		 */
		sleep(1);
		poll_pidfd(test_name, pidfd);
	}

	if (ret == pid)
		ksft_print_msg("Parent: Child process waited for.\n");

	time_t since_child_exit = time(NULL) - *child_exit_secs;

	ksft_print_msg("Time since child exit: %lu\n", since_child_exit);

	close(pidfd);

	if (since_child_exit < CHILD_THREAD_MIN_WAIT ||
			since_child_exit > CHILD_THREAD_MIN_WAIT + 2)
		ksft_exit_fail_msg("%s test: Failed\n", test_name);
	else
		ksft_test_result_pass("%s test: Passed\n", test_name);
}