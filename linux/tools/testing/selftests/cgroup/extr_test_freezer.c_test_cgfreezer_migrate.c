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
 scalar_t__ cg_check_frozen (char*,int) ; 
 scalar_t__ cg_create (char*) ; 
 int /*<<< orphan*/  cg_destroy (char*) ; 
 scalar_t__ cg_enter_and_wait_for_frozen (char*,int,int) ; 
 scalar_t__ cg_freeze_wait (char*,int) ; 
 char* cg_name (char const*,char*) ; 
 int cg_run_nowait (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cg_wait_for_proc_count (char*,int) ; 
 int /*<<< orphan*/  child_fn ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static int test_cgfreezer_migrate(const char *root)
{
	int ret = KSFT_FAIL;
	char *cgroup[2] = {0};
	int pid;

	cgroup[0] = cg_name(root, "cg_test_migrate_A");
	if (!cgroup[0])
		goto cleanup;

	cgroup[1] = cg_name(root, "cg_test_migrate_B");
	if (!cgroup[1])
		goto cleanup;

	if (cg_create(cgroup[0]))
		goto cleanup;

	if (cg_create(cgroup[1]))
		goto cleanup;

	pid = cg_run_nowait(cgroup[0], child_fn, NULL);
	if (pid < 0)
		goto cleanup;

	if (cg_wait_for_proc_count(cgroup[0], 1))
		goto cleanup;

	/*
	 * Migrate from A (running) to B (frozen)
	 */
	if (cg_freeze_wait(cgroup[1], true))
		goto cleanup;

	if (cg_enter_and_wait_for_frozen(cgroup[1], pid, true))
		goto cleanup;

	if (cg_check_frozen(cgroup[0], false))
		goto cleanup;

	/*
	 * Migrate from B (frozen) to A (running)
	 */
	if (cg_enter_and_wait_for_frozen(cgroup[0], pid, false))
		goto cleanup;

	if (cg_check_frozen(cgroup[1], true))
		goto cleanup;

	/*
	 * Migrate from A (frozen) to B (frozen)
	 */
	if (cg_freeze_wait(cgroup[0], true))
		goto cleanup;

	if (cg_enter_and_wait_for_frozen(cgroup[1], pid, true))
		goto cleanup;

	if (cg_check_frozen(cgroup[0], true))
		goto cleanup;

	ret = KSFT_PASS;

cleanup:
	if (cgroup[0])
		cg_destroy(cgroup[0]);
	free(cgroup[0]);
	if (cgroup[1])
		cg_destroy(cgroup[1]);
	free(cgroup[1]);
	return ret;
}