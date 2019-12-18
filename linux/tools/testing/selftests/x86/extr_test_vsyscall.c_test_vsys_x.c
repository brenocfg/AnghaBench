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
 int /*<<< orphan*/  jmpbuf ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int segv_err ; 
 scalar_t__ sigsetjmp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vgtod (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ vsyscall_map_x ; 

__attribute__((used)) static int test_vsys_x(void)
{
#ifdef __x86_64__
	if (vsyscall_map_x) {
		/* We already tested this adequately. */
		return 0;
	}

	printf("[RUN]\tMake sure that vsyscalls really page fault\n");

	bool can_exec;
	if (sigsetjmp(jmpbuf, 1) == 0) {
		vgtod(NULL, NULL);
		can_exec = true;
	} else {
		can_exec = false;
	}

	if (can_exec) {
		printf("[FAIL]\tExecuting the vsyscall did not page fault\n");
		return 1;
	} else if (segv_err & (1 << 4)) { /* INSTR */
		printf("[OK]\tExecuting the vsyscall page failed: #PF(0x%lx)\n",
		       segv_err);
	} else {
		printf("[FAIL]\tExecution failed with the wrong error: #PF(0x%lx)\n",
		       segv_err);
		return 1;
	}
#endif

	return 0;
}