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
 int KSFT_SKIP ; 
 scalar_t__ cg_create (char*) ; 
 int /*<<< orphan*/  cg_destroy (char*) ; 
 scalar_t__ cg_enter_current (char const*) ; 
 char* cg_name (char const*,char*) ; 
 scalar_t__ cg_read_strstr (char const*,char*,char*) ; 
 scalar_t__ cg_write (char const*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static int test_cgcore_no_internal_process_constraint_on_threads(const char *root)
{
	int ret = KSFT_FAIL;
	char *parent = NULL, *child = NULL;

	if (cg_read_strstr(root, "cgroup.controllers", "cpu") ||
	    cg_write(root, "cgroup.subtree_control", "+cpu")) {
		ret = KSFT_SKIP;
		goto cleanup;
	}

	parent = cg_name(root, "cg_test_parent");
	child = cg_name(root, "cg_test_parent/cg_test_child");
	if (!parent || !child)
		goto cleanup;

	if (cg_create(parent))
		goto cleanup;

	if (cg_create(child))
		goto cleanup;

	if (cg_write(parent, "cgroup.type", "threaded"))
		goto cleanup;

	if (cg_write(child, "cgroup.type", "threaded"))
		goto cleanup;

	if (cg_write(parent, "cgroup.subtree_control", "+cpu"))
		goto cleanup;

	if (cg_enter_current(parent))
		goto cleanup;

	ret = KSFT_PASS;

cleanup:
	cg_enter_current(root);
	cg_enter_current(root);
	if (child)
		cg_destroy(child);
	if (parent)
		cg_destroy(parent);
	free(child);
	free(parent);
	return ret;
}