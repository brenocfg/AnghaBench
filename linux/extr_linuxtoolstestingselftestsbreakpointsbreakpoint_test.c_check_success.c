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

/* Variables and functions */
 int /*<<< orphan*/  PTRACE_PEEKDATA ; 
 int /*<<< orphan*/  PTRACE_POKEDATA ; 
 scalar_t__ SIGTRAP ; 
 scalar_t__ WSTOPSIG (int) ; 
 int /*<<< orphan*/  child_pid ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksft_test_result_fail (char const*) ; 
 int /*<<< orphan*/  ksft_test_result_pass (char const*) ; 
 int nr_tests ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int trapped ; 
 int /*<<< orphan*/  wait (int*) ; 

__attribute__((used)) static void check_success(const char *msg)
{
	int child_nr_tests;
	int status;
	int ret;

	/* Wait for the child to SIGTRAP */
	wait(&status);

	ret = 0;

	if (WSTOPSIG(status) == SIGTRAP) {
		child_nr_tests = ptrace(PTRACE_PEEKDATA, child_pid,
					&nr_tests, 0);
		if (child_nr_tests == nr_tests)
			ret = 1;
		if (ptrace(PTRACE_POKEDATA, child_pid, &trapped, 1))
			ksft_exit_fail_msg("Can't poke: %s\n", strerror(errno));
	}

	nr_tests++;

	if (ret)
		ksft_test_result_pass(msg);
	else
		ksft_test_result_fail(msg);
}