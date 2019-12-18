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
struct btrfs_fs_info {int nodesize; } ;

/* Variables and functions */
 int btrfs_calc_insert_metadata_size (struct btrfs_fs_info*,int) ; 
 int btrfs_calc_metadata_size (struct btrfs_fs_info*,int) ; 
 int btrfs_csum_bytes_to_leaves (struct btrfs_fs_info*,int) ; 
 int count_max_extents (int) ; 

__attribute__((used)) static void calc_inode_reservations(struct btrfs_fs_info *fs_info,
				    u64 num_bytes, u64 *meta_reserve,
				    u64 *qgroup_reserve)
{
	u64 nr_extents = count_max_extents(num_bytes);
	u64 csum_leaves = btrfs_csum_bytes_to_leaves(fs_info, num_bytes);
	u64 inode_update = btrfs_calc_metadata_size(fs_info, 1);

	*meta_reserve = btrfs_calc_insert_metadata_size(fs_info,
						nr_extents + csum_leaves);

	/*
	 * finish_ordered_io has to update the inode, so add the space required
	 * for an inode update.
	 */
	*meta_reserve += inode_update;
	*qgroup_reserve = nr_extents * fs_info->nodesize;
}