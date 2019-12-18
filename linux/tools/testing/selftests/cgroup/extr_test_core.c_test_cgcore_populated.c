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
 scalar_t__ cg_enter_current (char const*) ; 
 char* cg_name (char const*,char*) ; 
 scalar_t__ cg_read_strcmp (char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static int test_cgcore_populated(const char *root)
{
	int ret = KSFT_FAIL;
	char *cg_test_a = NULL, *cg_test_b = NULL;
	char *cg_test_c = NULL, *cg_test_d = NULL;

	cg_test_a = cg_name(root, "cg_test_a");
	cg_test_b = cg_name(root, "cg_test_a/cg_test_b");
	cg_test_c = cg_name(root, "cg_test_a/cg_test_b/cg_test_c");
	cg_test_d = cg_name(root, "cg_test_a/cg_test_b/cg_test_d");

	if (!cg_test_a || !cg_test_b || !cg_test_c || !cg_test_d)
		goto cleanup;

	if (cg_create(cg_test_a))
		goto cleanup;

	if (cg_create(cg_test_b))
		goto cleanup;

	if (cg_create(cg_test_c))
		goto cleanup;

	if (cg_create(cg_test_d))
		goto cleanup;

	if (cg_enter_current(cg_test_c))
		goto cleanup;

	if (cg_read_strcmp(cg_test_a, "cgroup.events", "populated 1\n"))
		goto cleanup;

	if (cg_read_strcmp(cg_test_b, "cgroup.events", "populated 1\n"))
		goto cleanup;

	if (cg_read_strcmp(cg_test_c, "cgroup.events", "populated 1\n"))
		goto cleanup;

	if (cg_read_strcmp(cg_test_d, "cgroup.events", "populated 0\n"))
		goto cleanup;

	if (cg_enter_current(root))
		goto cleanup;

	if (cg_read_strcmp(cg_test_a, "cgroup.events", "populated 0\n"))
		goto cleanup;

	if (cg_read_strcmp(cg_test_b, "cgroup.events", "populated 0\n"))
		goto cleanup;

	if (cg_read_strcmp(cg_test_c, "cgroup.events", "populated 0\n"))
		goto cleanup;

	if (cg_read_strcmp(cg_test_d, "cgroup.events", "populated 0\n"))
		goto cleanup;

	ret = KSFT_PASS;

cleanup:
	if (cg_test_d)
		cg_destroy(cg_test_d);
	if (cg_test_c)
		cg_destroy(cg_test_c);
	if (cg_test_b)
		cg_destroy(cg_test_b);
	if (cg_test_a)
		cg_destroy(cg_test_a);
	free(cg_test_d);
	free(cg_test_c);
	free(cg_test_b);
	free(cg_test_a);
	return ret;
}