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
 int ARRAY_SIZE (char**) ; 
 int KSFT_FAIL ; 
 int KSFT_PASS ; 
 scalar_t__ MB (int) ; 
 int /*<<< orphan*/  alloc_anon ; 
 int /*<<< orphan*/  alloc_pagecache_50M ; 
 scalar_t__ cg_create (char*) ; 
 int /*<<< orphan*/  cg_destroy (char*) ; 
 char* cg_name (char const*,char*) ; 
 char* cg_name_indexed (char*,char*,int) ; 
 long cg_read_key_long (char*,char*,char*) ; 
 long cg_read_long (char*,char*) ; 
 scalar_t__ cg_run (char*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ cg_write (char*,char*,char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int get_temp_fd () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  values_close (long,scalar_t__,int) ; 

__attribute__((used)) static int test_memcg_low(const char *root)
{
	int ret = KSFT_FAIL;
	char *parent[3] = {NULL};
	char *children[4] = {NULL};
	long low, oom;
	long c[4];
	int i;
	int fd;

	fd = get_temp_fd();
	if (fd < 0)
		goto cleanup;

	parent[0] = cg_name(root, "memcg_test_0");
	if (!parent[0])
		goto cleanup;

	parent[1] = cg_name(parent[0], "memcg_test_1");
	if (!parent[1])
		goto cleanup;

	parent[2] = cg_name(parent[0], "memcg_test_2");
	if (!parent[2])
		goto cleanup;

	if (cg_create(parent[0]))
		goto cleanup;

	if (cg_read_long(parent[0], "memory.low"))
		goto cleanup;

	if (cg_write(parent[0], "cgroup.subtree_control", "+memory"))
		goto cleanup;

	if (cg_write(parent[0], "memory.max", "200M"))
		goto cleanup;

	if (cg_write(parent[0], "memory.swap.max", "0"))
		goto cleanup;

	if (cg_create(parent[1]))
		goto cleanup;

	if (cg_write(parent[1], "cgroup.subtree_control", "+memory"))
		goto cleanup;

	if (cg_create(parent[2]))
		goto cleanup;

	for (i = 0; i < ARRAY_SIZE(children); i++) {
		children[i] = cg_name_indexed(parent[1], "child_memcg", i);
		if (!children[i])
			goto cleanup;

		if (cg_create(children[i]))
			goto cleanup;

		if (i == 2)
			continue;

		if (cg_run(children[i], alloc_pagecache_50M, (void *)(long)fd))
			goto cleanup;
	}

	if (cg_write(parent[0], "memory.low", "50M"))
		goto cleanup;
	if (cg_write(parent[1], "memory.low", "50M"))
		goto cleanup;
	if (cg_write(children[0], "memory.low", "75M"))
		goto cleanup;
	if (cg_write(children[1], "memory.low", "25M"))
		goto cleanup;
	if (cg_write(children[2], "memory.low", "500M"))
		goto cleanup;
	if (cg_write(children[3], "memory.low", "0"))
		goto cleanup;

	if (cg_run(parent[2], alloc_anon, (void *)MB(148)))
		goto cleanup;

	if (!values_close(cg_read_long(parent[1], "memory.current"), MB(50), 3))
		goto cleanup;

	for (i = 0; i < ARRAY_SIZE(children); i++)
		c[i] = cg_read_long(children[i], "memory.current");

	if (!values_close(c[0], MB(33), 10))
		goto cleanup;

	if (!values_close(c[1], MB(17), 10))
		goto cleanup;

	if (!values_close(c[2], 0, 1))
		goto cleanup;

	if (cg_run(parent[2], alloc_anon, (void *)MB(166))) {
		fprintf(stderr,
			"memory.low prevents from allocating anon memory\n");
		goto cleanup;
	}

	for (i = 0; i < ARRAY_SIZE(children); i++) {
		oom = cg_read_key_long(children[i], "memory.events", "oom ");
		low = cg_read_key_long(children[i], "memory.events", "low ");

		if (oom)
			goto cleanup;
		if (i < 2 && low <= 0)
			goto cleanup;
		if (i >= 2 && low)
			goto cleanup;
	}

	ret = KSFT_PASS;

cleanup:
	for (i = ARRAY_SIZE(children) - 1; i >= 0; i--) {
		if (!children[i])
			continue;

		cg_destroy(children[i]);
		free(children[i]);
	}

	for (i = ARRAY_SIZE(parent) - 1; i >= 0; i--) {
		if (!parent[i])
			continue;

		cg_destroy(parent[i]);
		free(parent[i]);
	}
	close(fd);
	return ret;
}