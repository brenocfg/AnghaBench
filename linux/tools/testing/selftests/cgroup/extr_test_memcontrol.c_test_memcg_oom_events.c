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
 scalar_t__ MB (int) ; 
 int /*<<< orphan*/  alloc_anon ; 
 scalar_t__ cg_create (char*) ; 
 int /*<<< orphan*/  cg_destroy (char*) ; 
 char* cg_name (char const*,char*) ; 
 int cg_read_key_long (char*,char*,char*) ; 
 scalar_t__ cg_read_strcmp (char*,char*,char*) ; 
 int /*<<< orphan*/  cg_run (char*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ cg_write (char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static int test_memcg_oom_events(const char *root)
{
	int ret = KSFT_FAIL;
	char *memcg;

	memcg = cg_name(root, "memcg_test");
	if (!memcg)
		goto cleanup;

	if (cg_create(memcg))
		goto cleanup;

	if (cg_write(memcg, "memory.max", "30M"))
		goto cleanup;

	if (cg_write(memcg, "memory.swap.max", "0"))
		goto cleanup;

	if (!cg_run(memcg, alloc_anon, (void *)MB(100)))
		goto cleanup;

	if (cg_read_strcmp(memcg, "cgroup.procs", ""))
		goto cleanup;

	if (cg_read_key_long(memcg, "memory.events", "oom ") != 1)
		goto cleanup;

	if (cg_read_key_long(memcg, "memory.events", "oom_kill ") != 1)
		goto cleanup;

	ret = KSFT_PASS;

cleanup:
	cg_destroy(memcg);
	free(memcg);

	return ret;
}