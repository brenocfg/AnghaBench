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

/* Variables and functions */
 int /*<<< orphan*/  SKIP_IF (int) ; 
 scalar_t__ child_pid ; 
 int dawr_present () ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  get_dbginfo () ; 
 int /*<<< orphan*/  hwbreak_present () ; 
 int launch_tests (int) ; 
 int /*<<< orphan*/  trigger_tests () ; 
 int /*<<< orphan*/  wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ptrace_hwbreak(void)
{
	pid_t pid;
	int ret;
	bool dawr;

	pid = fork();
	if (!pid) {
		trigger_tests();
		return 0;
	}

	wait(NULL);

	child_pid = pid;

	get_dbginfo();
	SKIP_IF(!hwbreak_present());
	dawr = dawr_present();

	ret = launch_tests(dawr);

	wait(NULL);

	return ret;
}