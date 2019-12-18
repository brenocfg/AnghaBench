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
 int /*<<< orphan*/  PPC_PTRACE_DELHWDEBUG ; 
 int /*<<< orphan*/  child_pid ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int del_hwbreakpoint_addr(int watchpoint_handle)
{
	int ret;

	ret = ptrace(PPC_PTRACE_DELHWDEBUG, child_pid, 0, watchpoint_handle);
	if (ret < 0) {
		perror("Can't delete hw breakpoint\n");
		exit(-1);
	}
	return ret;
}