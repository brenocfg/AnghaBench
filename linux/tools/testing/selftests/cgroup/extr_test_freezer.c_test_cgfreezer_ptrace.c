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
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 int KSFT_FAIL ; 
 int KSFT_PASS ; 
 int /*<<< orphan*/  PTRACE_DETACH ; 
 int /*<<< orphan*/  PTRACE_GETSIGINFO ; 
 int /*<<< orphan*/  PTRACE_INTERRUPT ; 
 int /*<<< orphan*/  PTRACE_SEIZE ; 
 scalar_t__ cg_check_frozen (char*,int) ; 
 scalar_t__ cg_create (char*) ; 
 int /*<<< orphan*/  cg_destroy (char*) ; 
 scalar_t__ cg_freeze_wait (char*,int) ; 
 char* cg_name (char const*,char*) ; 
 int cg_run_nowait (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cg_wait_for_proc_count (char*,int) ; 
 int /*<<< orphan*/  child_fn ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_cgfreezer_ptrace(const char *root)
{
	int ret = KSFT_FAIL;
	char *cgroup = NULL;
	siginfo_t siginfo;
	int pid;

	cgroup = cg_name(root, "cg_test_ptrace");
	if (!cgroup)
		goto cleanup;

	if (cg_create(cgroup))
		goto cleanup;

	pid = cg_run_nowait(cgroup, child_fn, NULL);
	if (pid < 0)
		goto cleanup;

	if (cg_wait_for_proc_count(cgroup, 1))
		goto cleanup;

	if (cg_freeze_wait(cgroup, true))
		goto cleanup;

	if (ptrace(PTRACE_SEIZE, pid, NULL, NULL))
		goto cleanup;

	if (ptrace(PTRACE_INTERRUPT, pid, NULL, NULL))
		goto cleanup;

	waitpid(pid, NULL, 0);

	/*
	 * Cgroup has to remain frozen, however the test task
	 * is in traced state.
	 */
	if (cg_check_frozen(cgroup, true))
		goto cleanup;

	if (ptrace(PTRACE_GETSIGINFO, pid, NULL, &siginfo))
		goto cleanup;

	if (ptrace(PTRACE_DETACH, pid, NULL, NULL))
		goto cleanup;

	if (cg_check_frozen(cgroup, true))
		goto cleanup;

	ret = KSFT_PASS;

cleanup:
	if (cgroup)
		cg_destroy(cgroup);
	free(cgroup);
	return ret;
}