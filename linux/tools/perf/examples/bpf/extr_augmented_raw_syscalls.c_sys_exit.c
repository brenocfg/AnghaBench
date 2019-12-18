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
struct syscall_exit_args {int /*<<< orphan*/  syscall_nr; } ;
typedef  int /*<<< orphan*/  exit_args ;

/* Variables and functions */
 int /*<<< orphan*/  bpf_tail_call (struct syscall_exit_args*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__ pid_filter__has (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pids_filtered ; 
 int /*<<< orphan*/  probe_read (struct syscall_exit_args*,int,struct syscall_exit_args*) ; 
 int /*<<< orphan*/  syscalls_sys_exit ; 

int sys_exit(struct syscall_exit_args *args)
{
	struct syscall_exit_args exit_args;

	if (pid_filter__has(&pids_filtered, getpid()))
		return 0;

	probe_read(&exit_args, sizeof(exit_args), args);
	/*
	 * Jump to syscall specific return augmenter, even if the default one,
	 * "!raw_syscalls:unaugmented" that will just return 1 to return the
	 * unagmented tracepoint payload.
	 */
	bpf_tail_call(args, &syscalls_sys_exit, exit_args.syscall_nr);
	/*
	 * If not found on the PROG_ARRAY syscalls map, then we're filtering it:
	 */
	return 0;
}