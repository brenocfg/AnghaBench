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
 int /*<<< orphan*/  EXTENT_FLAG_COMPRESSED ; 
 int /*<<< orphan*/  EXTENT_FLAG_PREALLOC ; 
 int /*<<< orphan*/  compressed_only ; 
 int /*<<< orphan*/  prealloc_only ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_btrfs_get_extent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int test_extent_accounting (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int test_hole_first (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_msg (char*) ; 

int btrfs_test_inodes(u32 sectorsize, u32 nodesize)
{
	int ret;

	test_msg("running inode tests");

	set_bit(EXTENT_FLAG_COMPRESSED, &compressed_only);
	set_bit(EXTENT_FLAG_PREALLOC, &prealloc_only);

	ret = test_btrfs_get_extent(sectorsize, nodesize);
	if (ret)
		return ret;
	ret = test_hole_first(sectorsize, nodesize);
	if (ret)
		return ret;
	return test_extent_accounting(sectorsize, nodesize);
}