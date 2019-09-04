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
 int /*<<< orphan*/  OOM_SCORE_ADJ_MIN ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  alloc_anon ; 
 int /*<<< orphan*/  alloc_anon_noexit ; 
 scalar_t__ cg_create (char*) ; 
 int /*<<< orphan*/  cg_destroy (char*) ; 
 char* cg_name (char const*,char*) ; 
 int cg_read_key_long (char*,char*,char*) ; 
 int /*<<< orphan*/  cg_run (char*,int /*<<< orphan*/ ,void*) ; 
 int cg_run_nowait (char*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ cg_write (char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ kill (int,int /*<<< orphan*/ ) ; 
 scalar_t__ set_oom_adj_score (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_memcg_oom_group_score_events(const char *root)
{
	int ret = KSFT_FAIL;
	char *memcg;
	int safe_pid;

	memcg = cg_name(root, "memcg_test_0");

	if (!memcg)
		goto cleanup;

	if (cg_create(memcg))
		goto cleanup;

	if (cg_write(memcg, "memory.max", "50M"))
		goto cleanup;

	if (cg_write(memcg, "memory.swap.max", "0"))
		goto cleanup;

	if (cg_write(memcg, "memory.oom.group", "1"))
		goto cleanup;

	safe_pid = cg_run_nowait(memcg, alloc_anon_noexit, (void *) MB(1));
	if (set_oom_adj_score(safe_pid, OOM_SCORE_ADJ_MIN))
		goto cleanup;

	cg_run_nowait(memcg, alloc_anon_noexit, (void *) MB(1));
	if (!cg_run(memcg, alloc_anon, (void *)MB(100)))
		goto cleanup;

	if (cg_read_key_long(memcg, "memory.events", "oom_kill ") != 3)
		goto cleanup;

	if (kill(safe_pid, SIGKILL))
		goto cleanup;

	ret = KSFT_PASS;

cleanup:
	if (memcg)
		cg_destroy(memcg);
	free(memcg);

	return ret;
}