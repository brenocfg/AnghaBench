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

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int BTRFS_MAX_METADATA_BLOCKSIZE ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  btrfs_destroy_test_fs () ; 
 int btrfs_init_test_fs () ; 
 int btrfs_test_extent_buffer_operations (int,int) ; 
 int btrfs_test_extent_io (int,int) ; 
 int btrfs_test_extent_map () ; 
 int btrfs_test_free_space_cache (int,int) ; 
 int btrfs_test_free_space_tree (int,int) ; 
 int btrfs_test_inodes (int,int) ; 
 int btrfs_test_qgroups (int,int) ; 
 int /*<<< orphan*/  pr_info (char*,int,int) ; 

int btrfs_run_sanity_tests(void)
{
	int ret, i;
	u32 sectorsize, nodesize;
	u32 test_sectorsize[] = {
		PAGE_SIZE,
	};
	ret = btrfs_init_test_fs();
	if (ret)
		return ret;
	for (i = 0; i < ARRAY_SIZE(test_sectorsize); i++) {
		sectorsize = test_sectorsize[i];
		for (nodesize = sectorsize;
		     nodesize <= BTRFS_MAX_METADATA_BLOCKSIZE;
		     nodesize <<= 1) {
			pr_info("BTRFS: selftest: sectorsize: %u  nodesize: %u\n",
				sectorsize, nodesize);
			ret = btrfs_test_free_space_cache(sectorsize, nodesize);
			if (ret)
				goto out;
			ret = btrfs_test_extent_buffer_operations(sectorsize,
				nodesize);
			if (ret)
				goto out;
			ret = btrfs_test_extent_io(sectorsize, nodesize);
			if (ret)
				goto out;
			ret = btrfs_test_inodes(sectorsize, nodesize);
			if (ret)
				goto out;
			ret = btrfs_test_qgroups(sectorsize, nodesize);
			if (ret)
				goto out;
			ret = btrfs_test_free_space_tree(sectorsize, nodesize);
			if (ret)
				goto out;
		}
	}
	ret = btrfs_test_extent_map();

out:
	btrfs_destroy_test_fs();
	return ret;
}