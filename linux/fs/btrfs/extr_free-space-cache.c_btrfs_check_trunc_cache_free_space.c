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
typedef  scalar_t__ u64 ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_block_rsv {scalar_t__ reserved; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ btrfs_calc_insert_metadata_size (struct btrfs_fs_info*,int) ; 
 scalar_t__ btrfs_calc_metadata_size (struct btrfs_fs_info*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int btrfs_check_trunc_cache_free_space(struct btrfs_fs_info *fs_info,
				       struct btrfs_block_rsv *rsv)
{
	u64 needed_bytes;
	int ret;

	/* 1 for slack space, 1 for updating the inode */
	needed_bytes = btrfs_calc_insert_metadata_size(fs_info, 1) +
		btrfs_calc_metadata_size(fs_info, 1);

	spin_lock(&rsv->lock);
	if (rsv->reserved < needed_bytes)
		ret = -ENOSPC;
	else
		ret = 0;
	spin_unlock(&rsv->lock);
	return ret;
}