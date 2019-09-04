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
struct shared_info {unsigned long amr1; unsigned long amr2; unsigned long amr3; unsigned long expected_iamr; unsigned long new_iamr; unsigned long expected_uamor; unsigned long new_uamor; int /*<<< orphan*/  child_sync; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  NT_PPC_PKEY ; 
 int /*<<< orphan*/  PARENT_FAIL_IF (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PARENT_SKIP_IF_UNSUPPORTED (int,int /*<<< orphan*/ *) ; 
 int TEST_FAIL ; 
 int TEST_PASS ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int prod_child (int /*<<< orphan*/ *) ; 
 int ptrace_read_regs (int,int /*<<< orphan*/ ,unsigned long*,int) ; 
 char* ptrace_read_running ; 
 int ptrace_write_regs (int,int /*<<< orphan*/ ,unsigned long*,int) ; 
 char* ptrace_write_running ; 
 int wait (int*) ; 
 int wait_child (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int parent(struct shared_info *info, pid_t pid)
{
	unsigned long regs[3];
	int ret, status;

	/*
	 * Get the initial values for AMR, IAMR and UAMOR and communicate them
	 * to the child.
	 */
	ret = ptrace_read_regs(pid, NT_PPC_PKEY, regs, 3);
	PARENT_SKIP_IF_UNSUPPORTED(ret, &info->child_sync);
	PARENT_FAIL_IF(ret, &info->child_sync);

	info->amr1 = info->amr2 = info->amr3 = regs[0];
	info->expected_iamr = info->new_iamr = regs[1];
	info->expected_uamor = info->new_uamor = regs[2];

	/* Wake up child so that it can set itself up. */
	ret = prod_child(&info->child_sync);
	PARENT_FAIL_IF(ret, &info->child_sync);

	ret = wait_child(&info->child_sync);
	if (ret)
		return ret;

	/* Verify that we can read the pkey registers from the child. */
	ret = ptrace_read_regs(pid, NT_PPC_PKEY, regs, 3);
	PARENT_FAIL_IF(ret, &info->child_sync);

	printf("%-30s AMR: %016lx IAMR: %016lx UAMOR: %016lx\n",
	       ptrace_read_running, regs[0], regs[1], regs[2]);

	PARENT_FAIL_IF(regs[0] != info->amr1, &info->child_sync);
	PARENT_FAIL_IF(regs[1] != info->expected_iamr, &info->child_sync);
	PARENT_FAIL_IF(regs[2] != info->expected_uamor, &info->child_sync);

	/* Write valid AMR value in child. */
	ret = ptrace_write_regs(pid, NT_PPC_PKEY, &info->amr2, 1);
	PARENT_FAIL_IF(ret, &info->child_sync);

	printf("%-30s AMR: %016lx\n", ptrace_write_running, info->amr2);

	/* Wake up child so that it can verify it changed. */
	ret = prod_child(&info->child_sync);
	PARENT_FAIL_IF(ret, &info->child_sync);

	ret = wait_child(&info->child_sync);
	if (ret)
		return ret;

	/* Write invalid AMR value in child. */
	ret = ptrace_write_regs(pid, NT_PPC_PKEY, &info->amr3, 1);
	PARENT_FAIL_IF(ret, &info->child_sync);

	printf("%-30s AMR: %016lx\n", ptrace_write_running, info->amr3);

	/* Wake up child so that it can verify it didn't change. */
	ret = prod_child(&info->child_sync);
	PARENT_FAIL_IF(ret, &info->child_sync);

	ret = wait_child(&info->child_sync);
	if (ret)
		return ret;

	/* Try to write to IAMR. */
	regs[0] = info->amr1;
	regs[1] = info->new_iamr;
	ret = ptrace_write_regs(pid, NT_PPC_PKEY, regs, 2);
	PARENT_FAIL_IF(!ret, &info->child_sync);

	printf("%-30s AMR: %016lx IAMR: %016lx\n",
	       ptrace_write_running, regs[0], regs[1]);

	/* Try to write to IAMR and UAMOR. */
	regs[2] = info->new_uamor;
	ret = ptrace_write_regs(pid, NT_PPC_PKEY, regs, 3);
	PARENT_FAIL_IF(!ret, &info->child_sync);

	printf("%-30s AMR: %016lx IAMR: %016lx UAMOR: %016lx\n",
	       ptrace_write_running, regs[0], regs[1], regs[2]);

	/* Verify that all registers still have their expected values. */
	ret = ptrace_read_regs(pid, NT_PPC_PKEY, regs, 3);
	PARENT_FAIL_IF(ret, &info->child_sync);

	printf("%-30s AMR: %016lx IAMR: %016lx UAMOR: %016lx\n",
	       ptrace_read_running, regs[0], regs[1], regs[2]);

	PARENT_FAIL_IF(regs[0] != info->amr2, &info->child_sync);
	PARENT_FAIL_IF(regs[1] != info->expected_iamr, &info->child_sync);
	PARENT_FAIL_IF(regs[2] != info->expected_uamor, &info->child_sync);

	/* Wake up child so that it can verify AMR didn't change and wrap up. */
	ret = prod_child(&info->child_sync);
	PARENT_FAIL_IF(ret, &info->child_sync);

	ret = wait(&status);
	if (ret != pid) {
		printf("Child's exit status not captured\n");
		ret = TEST_PASS;
	} else if (!WIFEXITED(status)) {
		printf("Child exited abnormally\n");
		ret = TEST_FAIL;
	} else
		ret = WEXITSTATUS(status) ? TEST_FAIL : TEST_PASS;

	return ret;
}