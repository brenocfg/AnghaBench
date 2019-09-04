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
 int /*<<< orphan*/  PTRACE_ATTACH ; 
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int fpm_trace_signal(pid_t pid) /* {{{ */
{
	if (0 > ptrace(PTRACE_ATTACH, pid, 0, 0)) {
		zlog(ZLOG_SYSERROR, "failed to ptrace(ATTACH) child %d", pid);
		return -1;
	}
	return 0;
}