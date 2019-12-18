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
 int KSFT_FAIL ; 
 int KSFT_PASS ; 
 int /*<<< orphan*/  SIGSTOP ; 
 scalar_t__ cg_check_frozen (char*,int) ; 
 scalar_t__ cg_create (char*) ; 
 int /*<<< orphan*/  cg_destroy (char*) ; 
 scalar_t__ cg_freeze_wait (char*,int) ; 
 char* cg_name (char const*,char*) ; 
 int cg_run_nowait (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cg_wait_for_proc_count (char*,int) ; 
 int /*<<< orphan*/  child_fn ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ kill (int,int /*<<< orphan*/ ) ; 
 scalar_t__ proc_check_stopped (int) ; 

__attribute__((used)) static int test_cgfreezer_stopped(const char *root)
{
	int pid, ret = KSFT_FAIL;
	char *cgroup = NULL;

	cgroup = cg_name(root, "cg_test_stopped");
	if (!cgroup)
		goto cleanup;

	if (cg_create(cgroup))
		goto cleanup;

	pid = cg_run_nowait(cgroup, child_fn, NULL);

	if (cg_wait_for_proc_count(cgroup, 1))
		goto cleanup;

	if (kill(pid, SIGSTOP))
		goto cleanup;

	if (cg_check_frozen(cgroup, false))
		goto cleanup;

	if (cg_freeze_wait(cgroup, true))
		goto cleanup;

	if (cg_freeze_wait(cgroup, false))
		goto cleanup;

	if (proc_check_stopped(pid))
		goto cleanup;

	ret = KSFT_PASS;

cleanup:
	if (cgroup)
		cg_destroy(cgroup);
	free(cgroup);
	return ret;
}