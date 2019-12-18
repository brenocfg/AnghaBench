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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int test_eb_bitmaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int test_find_delalloc (int /*<<< orphan*/ ) ; 
 int test_find_first_clear_extent_bit () ; 
 int /*<<< orphan*/  test_msg (char*) ; 

int btrfs_test_extent_io(u32 sectorsize, u32 nodesize)
{
	int ret;

	test_msg("running extent I/O tests");

	ret = test_find_delalloc(sectorsize);
	if (ret)
		goto out;

	ret = test_find_first_clear_extent_bit();
	if (ret)
		goto out;

	ret = test_eb_bitmaps(sectorsize, nodesize);
out:
	return ret;
}