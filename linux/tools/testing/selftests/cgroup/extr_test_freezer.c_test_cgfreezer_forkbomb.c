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
 scalar_t__ cg_killall (char*) ; 
 char* cg_name (char const*,char*) ; 
 int /*<<< orphan*/  cg_run_nowait (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ cg_wait_for_proc_count (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  forkbomb_fn ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static int test_cgfreezer_forkbomb(const char *root)
{
	int ret = KSFT_FAIL;
	char *cgroup = NULL;

	cgroup = cg_name(root, "cg_forkbomb_test");
	if (!cgroup)
		goto cleanup;

	if (cg_create(cgroup))
		goto cleanup;

	cg_run_nowait(cgroup, forkbomb_fn, NULL);

	usleep(100000);

	if (cg_freeze_wait(cgroup, true))
		goto cleanup;

	if (cg_killall(cgroup))
		goto cleanup;

	if (cg_wait_for_proc_count(cgroup, 0))
		goto cleanup;

	ret = KSFT_PASS;

cleanup:
	if (cgroup)
		cg_destroy(cgroup);
	free(cgroup);
	return ret;
}