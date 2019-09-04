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
 int /*<<< orphan*/  PTRACE_TRACEME ; 
 int /*<<< orphan*/  SIGCONT ; 
 int /*<<< orphan*/  bp_1 () ; 
 int /*<<< orphan*/  exit (int) ; 
 int fork () ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spawn_child(void)
{
	int child = fork();

	if (child == 0) {
		/*
		 * The child sets itself for as tracee and
		 * waits in signal for parent to trace it,
		 * then it calls bp_1 and quits.
		 */
		int err = ptrace(PTRACE_TRACEME, 0, NULL, NULL);

		if (err) {
			pr_debug("failed to PTRACE_TRACEME\n");
			exit(1);
		}

		raise(SIGCONT);
		bp_1();
		exit(0);
	}

	return child;
}