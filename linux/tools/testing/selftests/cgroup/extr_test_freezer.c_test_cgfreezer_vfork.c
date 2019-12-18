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
 scalar_t__ cg_create (char*) ; 
 int /*<<< orphan*/  cg_destroy (char*) ; 
 scalar_t__ cg_freeze_wait (char*,int) ; 
 char* cg_name (char const*,char*) ; 
 int /*<<< orphan*/  cg_run_nowait (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cg_wait_for_proc_count (char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  vfork_fn ; 

__attribute__((used)) static int test_cgfreezer_vfork(const char *root)
{
	int ret = KSFT_FAIL;
	char *cgroup = NULL;

	cgroup = cg_name(root, "cg_test_vfork");
	if (!cgroup)
		goto cleanup;

	if (cg_create(cgroup))
		goto cleanup;

	cg_run_nowait(cgroup, vfork_fn, NULL);

	if (cg_wait_for_proc_count(cgroup, 2))
		goto cleanup;

	if (cg_freeze_wait(cgroup, true))
		goto cleanup;

	ret = KSFT_PASS;

cleanup:
	if (cgroup)
		cg_destroy(cgroup);
	free(cgroup);
	return ret;
}