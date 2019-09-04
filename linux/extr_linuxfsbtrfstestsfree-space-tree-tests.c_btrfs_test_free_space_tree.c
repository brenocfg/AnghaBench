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
typedef  int u32 ;
typedef  int /*<<< orphan*/  test_func_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int BTRFS_FREE_SPACE_BITMAP_BITS ; 
 int PAGE_SIZE ; 
 int run_test_both_formats (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  test_empty_block_group ; 
 int /*<<< orphan*/  test_merge_both ; 
 int /*<<< orphan*/  test_merge_left ; 
 int /*<<< orphan*/  test_merge_none ; 
 int /*<<< orphan*/  test_merge_right ; 
 int /*<<< orphan*/  test_msg (char*) ; 
 int /*<<< orphan*/  test_remove_all ; 
 int /*<<< orphan*/  test_remove_beginning ; 
 int /*<<< orphan*/  test_remove_end ; 
 int /*<<< orphan*/  test_remove_middle ; 

int btrfs_test_free_space_tree(u32 sectorsize, u32 nodesize)
{
	test_func_t tests[] = {
		test_empty_block_group,
		test_remove_all,
		test_remove_beginning,
		test_remove_end,
		test_remove_middle,
		test_merge_left,
		test_merge_right,
		test_merge_both,
		test_merge_none,
	};
	u32 bitmap_alignment;
	int test_ret = 0;
	int i;

	/*
	 * Align some operations to a page to flush out bugs in the extent
	 * buffer bitmap handling of highmem.
	 */
	bitmap_alignment = BTRFS_FREE_SPACE_BITMAP_BITS * PAGE_SIZE;

	test_msg("running free space tree tests");
	for (i = 0; i < ARRAY_SIZE(tests); i++) {
		int ret;

		ret = run_test_both_formats(tests[i], sectorsize, nodesize,
					    sectorsize);
		if (ret)
			test_ret = ret;

		ret = run_test_both_formats(tests[i], sectorsize, nodesize,
					    bitmap_alignment);
		if (ret)
			test_ret = ret;
	}

	return test_ret;
}