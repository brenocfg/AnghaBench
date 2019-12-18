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
 scalar_t__ cg_freeze_nowait (char*,int) ; 
 scalar_t__ cg_freeze_wait (char*,int) ; 
 char* cg_name (char const*,char*) ; 
 int /*<<< orphan*/  cg_run_nowait (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cg_wait_for_proc_count (char*,int) ; 
 int /*<<< orphan*/  child_fn ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static int test_cgfreezer_tree(const char *root)
{
	char *cgroup[10] = {0};
	int ret = KSFT_FAIL;
	int i;

	cgroup[0] = cg_name(root, "cg_test_tree_A");
	if (!cgroup[0])
		goto cleanup;

	cgroup[1] = cg_name(cgroup[0], "B");
	if (!cgroup[1])
		goto cleanup;

	cgroup[2] = cg_name(cgroup[1], "C");
	if (!cgroup[2])
		goto cleanup;

	cgroup[3] = cg_name(cgroup[1], "D");
	if (!cgroup[3])
		goto cleanup;

	cgroup[4] = cg_name(cgroup[0], "E");
	if (!cgroup[4])
		goto cleanup;

	cgroup[5] = cg_name(cgroup[4], "F");
	if (!cgroup[5])
		goto cleanup;

	cgroup[6] = cg_name(cgroup[5], "G");
	if (!cgroup[6])
		goto cleanup;

	cgroup[7] = cg_name(cgroup[6], "H");
	if (!cgroup[7])
		goto cleanup;

	cgroup[8] = cg_name(cgroup[0], "I");
	if (!cgroup[8])
		goto cleanup;

	cgroup[9] = cg_name(cgroup[0], "K");
	if (!cgroup[9])
		goto cleanup;

	for (i = 0; i < 10; i++)
		if (cg_create(cgroup[i]))
			goto cleanup;

	cg_run_nowait(cgroup[2], child_fn, NULL);
	cg_run_nowait(cgroup[7], child_fn, NULL);
	cg_run_nowait(cgroup[9], child_fn, NULL);
	cg_run_nowait(cgroup[9], child_fn, NULL);
	cg_run_nowait(cgroup[9], child_fn, NULL);

	/*
	 * Wait until all child processes will enter
	 * corresponding cgroups.
	 */

	if (cg_wait_for_proc_count(cgroup[2], 1) ||
	    cg_wait_for_proc_count(cgroup[7], 1) ||
	    cg_wait_for_proc_count(cgroup[9], 3))
		goto cleanup;

	/*
	 * Freeze B.
	 */
	if (cg_freeze_wait(cgroup[1], true))
		goto cleanup;

	/*
	 * Freeze F.
	 */
	if (cg_freeze_wait(cgroup[5], true))
		goto cleanup;

	/*
	 * Freeze G.
	 */
	if (cg_freeze_wait(cgroup[6], true))
		goto cleanup;

	/*
	 * Check that A and E are not frozen.
	 */
	if (cg_check_frozen(cgroup[0], false))
		goto cleanup;

	if (cg_check_frozen(cgroup[4], false))
		goto cleanup;

	/*
	 * Freeze A. Check that A, B and E are frozen.
	 */
	if (cg_freeze_wait(cgroup[0], true))
		goto cleanup;

	if (cg_check_frozen(cgroup[1], true))
		goto cleanup;

	if (cg_check_frozen(cgroup[4], true))
		goto cleanup;

	/*
	 * Unfreeze B, F and G
	 */
	if (cg_freeze_nowait(cgroup[1], false))
		goto cleanup;

	if (cg_freeze_nowait(cgroup[5], false))
		goto cleanup;

	if (cg_freeze_nowait(cgroup[6], false))
		goto cleanup;

	/*
	 * Check that C and H are still frozen.
	 */
	if (cg_check_frozen(cgroup[2], true))
		goto cleanup;

	if (cg_check_frozen(cgroup[7], true))
		goto cleanup;

	/*
	 * Unfreeze A. Check that A, C and K are not frozen.
	 */
	if (cg_freeze_wait(cgroup[0], false))
		goto cleanup;

	if (cg_check_frozen(cgroup[2], false))
		goto cleanup;

	if (cg_check_frozen(cgroup[9], false))
		goto cleanup;

	ret = KSFT_PASS;

cleanup:
	for (i = 9; i >= 0 && cgroup[i]; i--) {
		cg_destroy(cgroup[i]);
		free(cgroup[i]);
	}

	return ret;
}