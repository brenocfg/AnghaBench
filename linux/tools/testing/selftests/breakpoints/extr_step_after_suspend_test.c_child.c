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
typedef  int /*<<< orphan*/  set ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PTRACE_TRACEME ; 
 int /*<<< orphan*/  SIGSTOP ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ksft_print_msg (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ raise (int /*<<< orphan*/ ) ; 
 scalar_t__ sched_setaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

void child(int cpu)
{
	cpu_set_t set;

	CPU_ZERO(&set);
	CPU_SET(cpu, &set);
	if (sched_setaffinity(0, sizeof(set), &set) != 0) {
		ksft_print_msg("sched_setaffinity() failed: %s\n",
			strerror(errno));
		_exit(1);
	}

	if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) != 0) {
		ksft_print_msg("ptrace(PTRACE_TRACEME) failed: %s\n",
			strerror(errno));
		_exit(1);
	}

	if (raise(SIGSTOP) != 0) {
		ksft_print_msg("raise(SIGSTOP) failed: %s\n", strerror(errno));
		_exit(1);
	}

	_exit(0);
}