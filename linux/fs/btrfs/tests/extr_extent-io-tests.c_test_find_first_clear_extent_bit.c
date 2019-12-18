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
typedef  int u64 ;
struct extent_io_tree {int dummy; } ;

/* Variables and functions */
 int CHUNK_ALLOCATED ; 
 int CHUNK_TRIMMED ; 
 int EINVAL ; 
 int /*<<< orphan*/  IO_TREE_SELFTEST ; 
 int SZ_1M ; 
 int SZ_2M ; 
 int SZ_32M ; 
 int SZ_4M ; 
 int SZ_512K ; 
 int SZ_64M ; 
 int SZ_8M ; 
 int /*<<< orphan*/  clear_extent_bits (struct extent_io_tree*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  extent_io_tree_init (int /*<<< orphan*/ *,struct extent_io_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  find_first_clear_extent_bit (struct extent_io_tree*,int,int*,int*,int) ; 
 int /*<<< orphan*/  set_extent_bits (struct extent_io_tree*,int,int,int) ; 
 int /*<<< orphan*/  test_err (char*,int,int) ; 
 int /*<<< orphan*/  test_msg (char*) ; 

__attribute__((used)) static int test_find_first_clear_extent_bit(void)
{
	struct extent_io_tree tree;
	u64 start, end;
	int ret = -EINVAL;

	test_msg("running find_first_clear_extent_bit test");
	extent_io_tree_init(NULL, &tree, IO_TREE_SELFTEST, NULL);

	/*
	 * Set 1M-4M alloc/discard and 32M-64M thus leaving a hole between
	 * 4M-32M
	 */
	set_extent_bits(&tree, SZ_1M, SZ_4M - 1,
			CHUNK_TRIMMED | CHUNK_ALLOCATED);

	find_first_clear_extent_bit(&tree, SZ_512K, &start, &end,
				    CHUNK_TRIMMED | CHUNK_ALLOCATED);

	if (start != 0 || end != SZ_1M - 1) {
		test_err("error finding beginning range: start %llu end %llu",
			 start, end);
		goto out;
	}

	/* Now add 32M-64M so that we have a hole between 4M-32M */
	set_extent_bits(&tree, SZ_32M, SZ_64M - 1,
			CHUNK_TRIMMED | CHUNK_ALLOCATED);

	/*
	 * Request first hole starting at 12M, we should get 4M-32M
	 */
	find_first_clear_extent_bit(&tree, 12 * SZ_1M, &start, &end,
				    CHUNK_TRIMMED | CHUNK_ALLOCATED);

	if (start != SZ_4M || end != SZ_32M - 1) {
		test_err("error finding trimmed range: start %llu end %llu",
			 start, end);
		goto out;
	}

	/*
	 * Search in the middle of allocated range, should get the next one
	 * available, which happens to be unallocated -> 4M-32M
	 */
	find_first_clear_extent_bit(&tree, SZ_2M, &start, &end,
				    CHUNK_TRIMMED | CHUNK_ALLOCATED);

	if (start != SZ_4M || end != SZ_32M - 1) {
		test_err("error finding next unalloc range: start %llu end %llu",
			 start, end);
		goto out;
	}

	/*
	 * Set 64M-72M with CHUNK_ALLOC flag, then search for CHUNK_TRIMMED flag
	 * being unset in this range, we should get the entry in range 64M-72M
	 */
	set_extent_bits(&tree, SZ_64M, SZ_64M + SZ_8M - 1, CHUNK_ALLOCATED);
	find_first_clear_extent_bit(&tree, SZ_64M + SZ_1M, &start, &end,
				    CHUNK_TRIMMED);

	if (start != SZ_64M || end != SZ_64M + SZ_8M - 1) {
		test_err("error finding exact range: start %llu end %llu",
			 start, end);
		goto out;
	}

	find_first_clear_extent_bit(&tree, SZ_64M - SZ_8M, &start, &end,
				    CHUNK_TRIMMED);

	/*
	 * Search in the middle of set range whose immediate neighbour doesn't
	 * have the bits set so it must be returned
	 */
	if (start != SZ_64M || end != SZ_64M + SZ_8M - 1) {
		test_err("error finding next alloc range: start %llu end %llu",
			 start, end);
		goto out;
	}

	/*
	 * Search beyond any known range, shall return after last known range
	 * and end should be -1
	 */
	find_first_clear_extent_bit(&tree, -1, &start, &end, CHUNK_TRIMMED);
	if (start != SZ_64M + SZ_8M || end != -1) {
		test_err(
		"error handling beyond end of range search: start %llu end %llu",
			start, end);
		goto out;
	}

	ret = 0;
out:
	clear_extent_bits(&tree, 0, (u64)-1, CHUNK_TRIMMED | CHUNK_ALLOCATED);

	return ret;
}