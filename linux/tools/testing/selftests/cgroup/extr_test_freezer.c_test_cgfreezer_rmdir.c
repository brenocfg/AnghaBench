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
 scalar_t__ cg_destroy (char*) ; 
 scalar_t__ cg_freeze_wait (char*,int) ; 
 char* cg_name (char const*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static int test_cgfreezer_rmdir(const char *root)
{
	int ret = KSFT_FAIL;
	char *parent, *child = NULL;

	parent = cg_name(root, "cg_test_rmdir_A");
	if (!parent)
		goto cleanup;

	child = cg_name(parent, "cg_test_rmdir_B");
	if (!child)
		goto cleanup;

	if (cg_create(parent))
		goto cleanup;

	if (cg_create(child))
		goto cleanup;

	if (cg_freeze_wait(parent, true))
		goto cleanup;

	if (cg_destroy(child))
		goto cleanup;

	if (cg_check_frozen(parent, true))
		goto cleanup;

	if (cg_create(child))
		goto cleanup;

	if (cg_check_frozen(child, true))
		goto cleanup;

	ret = KSFT_PASS;

cleanup:
	if (child)
		cg_destroy(child);
	free(child);
	if (parent)
		cg_destroy(parent);
	free(parent);
	return ret;
}