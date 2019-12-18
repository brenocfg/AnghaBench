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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  get_pid_from_fdinfo_file (int,char*,int) ; 
 int getpid () ; 
 int ksft_exit_fail () ; 
 int ksft_exit_pass () ; 
 int /*<<< orphan*/  ksft_print_msg (char*,int,...) ; 
 int /*<<< orphan*/  ksft_set_plan (int) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int sys_pidfd_open (int,int) ; 

int main(int argc, char **argv)
{
	int pidfd = -1, ret = 1;
	pid_t pid;

	ksft_set_plan(3);

	pidfd = sys_pidfd_open(-1, 0);
	if (pidfd >= 0) {
		ksft_print_msg(
			"%s - succeeded to open pidfd for invalid pid -1\n",
			strerror(errno));
		goto on_error;
	}
	ksft_test_result_pass("do not allow invalid pid test: passed\n");

	pidfd = sys_pidfd_open(getpid(), 1);
	if (pidfd >= 0) {
		ksft_print_msg(
			"%s - succeeded to open pidfd with invalid flag value specified\n",
			strerror(errno));
		goto on_error;
	}
	ksft_test_result_pass("do not allow invalid flag test: passed\n");

	pidfd = sys_pidfd_open(getpid(), 0);
	if (pidfd < 0) {
		ksft_print_msg("%s - failed to open pidfd\n", strerror(errno));
		goto on_error;
	}
	ksft_test_result_pass("open a new pidfd test: passed\n");

	pid = get_pid_from_fdinfo_file(pidfd, "Pid:", sizeof("Pid:") - 1);
	ksft_print_msg("pidfd %d refers to process with pid %d\n", pidfd, pid);

	ret = 0;

on_error:
	if (pidfd >= 0)
		close(pidfd);

	return !ret ? ksft_exit_pass() : ksft_exit_fail();
}