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
	char *parent, *child, *parent2 = NULL, *child2 = NULL;
	int ret = KSFT_FAIL;
	char buf[PAGE_SIZE];

	/* Create two nested cgroups with the memory controller enabled */
	parent = cg_name(root, "memcg_test_0");
	child = cg_name(root, "memcg_test_0/memcg_test_1");
	if (!parent || !child)
		goto cleanup_free;

	if (cg_create(parent))
		goto cleanup_free;

	if (cg_write(parent, "cgroup.subtree_control", "+memory"))
		goto cleanup_parent;

	if (cg_create(child))
		goto cleanup_parent;

	if (cg_read_strstr(child, "cgroup.controllers", "memory"))
		goto cleanup_child;

	/* Create two nested cgroups without enabling memory controller */
	parent2 = cg_name(root, "memcg_test_1");
	child2 = cg_name(root, "memcg_test_1/memcg_test_1");
	if (!parent2 || !child2)
		goto cleanup_free2;

	if (cg_create(parent2))
		goto cleanup_free2;

	if (cg_create(child2))
		goto cleanup_parent2;

	if (cg_read(child2, "cgroup.controllers", buf, sizeof(buf)))
		goto cleanup_all;

	if (!cg_read_strstr(child2, "cgroup.controllers", "memory"))
		goto cleanup_all;

	ret = KSFT_PASS;

cleanup_all:
	cg_destroy(child2);
cleanup_parent2:
	cg_destroy(parent2);
cleanup_free2:
	free(parent2);
	free(child2);
cleanup_child:
	cg_destroy(child);
cleanup_parent:
	cg_destroy(parent);
cleanup_free:
	free(parent);
	free(child);

	return ret;
}