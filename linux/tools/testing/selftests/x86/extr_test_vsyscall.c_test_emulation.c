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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTRAP ; 
 int X86_EFLAGS_TF ; 
 int get_eflags () ; 
 int num_vsyscall_traps ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  set_eflags (int) ; 
 int /*<<< orphan*/  sethandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigtrap ; 
 int /*<<< orphan*/  vsyscall_map_x ; 
 int /*<<< orphan*/  vtime (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int test_emulation(void)
{
	time_t tmp;
	bool is_native;

	if (!vsyscall_map_x)
		return 0;

	printf("[RUN]\tchecking that vsyscalls are emulated\n");
	sethandler(SIGTRAP, sigtrap, 0);
	set_eflags(get_eflags() | X86_EFLAGS_TF);
	vtime(&tmp);
	set_eflags(get_eflags() & ~X86_EFLAGS_TF);

	/*
	 * If vsyscalls are emulated, we expect a single trap in the
	 * vsyscall page -- the call instruction will trap with RIP
	 * pointing to the entry point before emulation takes over.
	 * In native mode, we expect two traps, since whatever code
	 * the vsyscall page contains will be more than just a ret
	 * instruction.
	 */
	is_native = (num_vsyscall_traps > 1);

	printf("[%s]\tvsyscalls are %s (%d instructions in vsyscall page)\n",
	       (is_native ? "FAIL" : "OK"),
	       (is_native ? "native" : "emulated"),
	       (int)num_vsyscall_traps);

	return is_native;
}