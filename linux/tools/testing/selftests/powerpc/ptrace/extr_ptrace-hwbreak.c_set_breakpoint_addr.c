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
 int /*<<< orphan*/  PTRACE_SET_DEBUGREG ; 
 int /*<<< orphan*/  child_pid ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void set_breakpoint_addr(void *addr)
{
	int ret;

	ret = ptrace(PTRACE_SET_DEBUGREG, child_pid, 0, addr);
	if (ret) {
		perror("Can't set breakpoint addr\n");
		exit(-1);
	}
}