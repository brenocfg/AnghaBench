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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int KSFT_FAIL ; 
 int KSFT_PASS ; 
 int PAGE_SIZE ; 
 scalar_t__ cg_create (char*) ; 
 int /*<<< orphan*/  cg_destroy (char*) ; 
 char* cg_name (char const*,char*) ; 
 scalar_t__ cg_read (char*,char*,char*,int) ; 
 scalar_t__ cg_read_strstr (char*,char*,char*) ; 
 scalar_t__ cg_write (char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static int test_memcg_subtree_control(const char *root)
{
	char *parent, *child, *parent2, *child2;
	int ret = KSFT_FAIL;
	char buf[PAGE_SIZE];

	/* Create two nested cgroups with the memory controller enabled */
	parent = cg_name(root, "memcg_test_0");
	child = cg_name(root, "memcg_test_0/memcg_test_1");
	if (!parent || !child)
		goto cleanup;

	if (cg_create(parent))
		goto cleanup;

	if (cg_write(parent, "cgroup.subtree_control", "+memory"))
		goto cleanup;

	if (cg_create(child))
		goto cleanup;

	if (cg_read_strstr(child, "cgroup.controllers", "memory"))
		goto cleanup;

	/* Create two nested cgroups without enabling memory controller */
	parent2 = cg_name(root, "memcg_test_1");
	child2 = cg_name(root, "memcg_test_1/memcg_test_1");
	if (!parent2 || !child2)
		goto cleanup;

	if (cg_create(parent2))
		goto cleanup;

	if (cg_create(child2))
		goto cleanup;

	if (cg_read(child2, "cgroup.controllers", buf, sizeof(buf)))
		goto cleanup;

	if (!cg_read_strstr(child2, "cgroup.controllers", "memory"))
		goto cleanup;

	ret = KSFT_PASS;

cleanup:
	cg_destroy(child);
	cg_destroy(parent);
	free(parent);
	free(child);

	cg_destroy(child2);
	cg_destroy(parent2);
	free(parent2);
	free(child2);

	return ret;
}