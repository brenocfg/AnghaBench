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
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_FAILURE ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int /*<<< orphan*/  mach_error_string (scalar_t__) ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int /*<<< orphan*/  target ; 
 scalar_t__ task_for_pid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,char*) ; 

int fpm_trace_ready(pid_t pid) /* {{{ */
{
	kern_return_t kr;

	kr = task_for_pid(mach_task_self(), pid, &target);
	if (kr != KERN_SUCCESS) {
		char *msg = "";

		if (kr == KERN_FAILURE) {
			msg = " It seems that master process does not have enough privileges to trace processes.";
		}
		zlog(ZLOG_ERROR, "task_for_pid() failed: %s (%d)%s", mach_error_string(kr), kr, msg);
		return -1;
	}
	return 0;
}