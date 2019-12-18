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
 long MB (int) ; 
 int /*<<< orphan*/  alloc_anon ; 
 int /*<<< orphan*/  alloc_pagecache_max_30M ; 
 scalar_t__ cg_create (char*) ; 
 int /*<<< orphan*/  cg_destroy (char*) ; 
 char* cg_name (char const*,char*) ; 
 long cg_read_key_long (char*,char*,char*) ; 
 long cg_read_long (char*,char*) ; 
 scalar_t__ cg_read_strcmp (char*,char*,char*) ; 
 scalar_t__ cg_run (char*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ cg_write (char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static int test_memcg_max(const char *root)
{
	int ret = KSFT_FAIL;
	char *memcg;
	long current, max;

	memcg = cg_name(root, "memcg_test");
	if (!memcg)
		goto cleanup;

	if (cg_create(memcg))
		goto cleanup;

	if (cg_read_strcmp(memcg, "memory.max", "max\n"))
		goto cleanup;

	if (cg_write(memcg, "memory.swap.max", "0"))
		goto cleanup;

	if (cg_write(memcg, "memory.max", "30M"))
		goto cleanup;

	/* Should be killed by OOM killer */
	if (!cg_run(memcg, alloc_anon, (void *)MB(100)))
		goto cleanup;

	if (cg_run(memcg, alloc_pagecache_max_30M, NULL))
		goto cleanup;

	current = cg_read_long(memcg, "memory.current");
	if (current > MB(30) || !current)
		goto cleanup;

	max = cg_read_key_long(memcg, "memory.events", "max ");
	if (max <= 0)
		goto cleanup;

	ret = KSFT_PASS;

cleanup:
	cg_destroy(memcg);
	free(memcg);

	return ret;
}