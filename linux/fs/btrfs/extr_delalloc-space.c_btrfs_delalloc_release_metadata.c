#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_inode {int /*<<< orphan*/  lock; int /*<<< orphan*/  csum_bytes; TYPE_1__* root; } ;
struct btrfs_fs_info {int /*<<< orphan*/  sectorsize; } ;
struct TYPE_2__ {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_calculate_inode_block_rsv_size (struct btrfs_fs_info*,struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_inode_rsv_release (struct btrfs_inode*,int) ; 
 scalar_t__ btrfs_is_testing (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void btrfs_delalloc_release_metadata(struct btrfs_inode *inode, u64 num_bytes,
				     bool qgroup_free)
{
	struct btrfs_fs_info *fs_info = inode->root->fs_info;

	num_bytes = ALIGN(num_bytes, fs_info->sectorsize);
	spin_lock(&inode->lock);
	inode->csum_bytes -= num_bytes;
	btrfs_calculate_inode_block_rsv_size(fs_info, inode);
	spin_unlock(&inode->lock);

	if (btrfs_is_testing(fs_info))
		return;

	btrfs_inode_rsv_release(inode, qgroup_free);
}