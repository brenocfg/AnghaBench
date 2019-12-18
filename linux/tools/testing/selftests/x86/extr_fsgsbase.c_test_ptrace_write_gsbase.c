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
 int /*<<< orphan*/  PTRACE_CONT ; 
 int /*<<< orphan*/  PTRACE_PEEKUSER ; 
 int /*<<< orphan*/  PTRACE_POKEUSER ; 
 int /*<<< orphan*/  PTRACE_TRACEME ; 
 scalar_t__ SIGTRAP ; 
 unsigned long USER_REGS_OFFSET (unsigned long) ; 
 scalar_t__ WSTOPSIG (int) ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ fork () ; 
 unsigned long gs_base ; 
 unsigned long load_gs () ; 
 int /*<<< orphan*/  nerrs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 unsigned long ptrace (int /*<<< orphan*/ ,scalar_t__,unsigned long,int) ; 
 int /*<<< orphan*/  raise (scalar_t__) ; 
 unsigned long* shared_scratch ; 
 int /*<<< orphan*/  wait (int*) ; 

__attribute__((used)) static void test_ptrace_write_gsbase(void)
{
	int status;
	pid_t child = fork();

	if (child < 0)
		err(1, "fork");

	if (child == 0) {
		printf("[RUN]\tPTRACE_POKE(), write GSBASE from ptracer\n");

		*shared_scratch = load_gs();

		if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) != 0)
			err(1, "PTRACE_TRACEME");

		raise(SIGTRAP);
		_exit(0);
	}

	wait(&status);

	if (WSTOPSIG(status) == SIGTRAP) {
		unsigned long gs, base;
		unsigned long gs_offset = USER_REGS_OFFSET(gs);
		unsigned long base_offset = USER_REGS_OFFSET(gs_base);

		gs = ptrace(PTRACE_PEEKUSER, child, gs_offset, NULL);

		if (gs != *shared_scratch) {
			nerrs++;
			printf("[FAIL]\tGS is not prepared with nonzero\n");
			goto END;
		}

		if (ptrace(PTRACE_POKEUSER, child, base_offset, 0xFF) != 0)
			err(1, "PTRACE_POKEUSER");

		gs = ptrace(PTRACE_PEEKUSER, child, gs_offset, NULL);
		base = ptrace(PTRACE_PEEKUSER, child, base_offset, NULL);

		/*
		 * In a non-FSGSBASE system, the nonzero selector will load
		 * GSBASE (again). But what is tested here is whether the
		 * selector value is changed or not by the GSBASE write in
		 * a ptracer.
		 */
		if (gs == 0 && base == 0xFF) {
			printf("[OK]\tGS was reset as expected\n");
		} else {
			nerrs++;
			printf("[FAIL]\tGS=0x%lx, GSBASE=0x%lx (should be 0, 0xFF)\n", gs, base);
		}
	}

END:
	ptrace(PTRACE_CONT, child, NULL, NULL);
}