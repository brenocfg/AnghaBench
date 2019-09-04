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
struct btrfs_root {int /*<<< orphan*/  fs_info; } ;
struct btrfs_block_rsv {scalar_t__ reserved; scalar_t__ size; scalar_t__ qgroup_rsv_reserved; scalar_t__ qgroup_rsv_size; int /*<<< orphan*/  lock; } ;
struct btrfs_inode {struct btrfs_block_rsv block_rsv; struct btrfs_root* root; } ;
typedef  enum btrfs_reserve_flush_enum { ____Placeholder_btrfs_reserve_flush_enum } btrfs_reserve_flush_enum ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  block_rsv_add_bytes (struct btrfs_block_rsv*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_ino (struct btrfs_inode*) ; 
 int /*<<< orphan*/  btrfs_qgroup_free_meta_prealloc (struct btrfs_root*,scalar_t__) ; 
 int btrfs_qgroup_reserve_meta_prealloc (struct btrfs_root*,scalar_t__,int) ; 
 int reserve_metadata_bytes (struct btrfs_root*,struct btrfs_block_rsv*,scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_space_reservation (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int btrfs_inode_rsv_refill(struct btrfs_inode *inode,
				  enum btrfs_reserve_flush_enum flush)
{
	struct btrfs_root *root = inode->root;
	struct btrfs_block_rsv *block_rsv = &inode->block_rsv;
	u64 num_bytes = 0;
	u64 qgroup_num_bytes = 0;
	int ret = -ENOSPC;

	spin_lock(&block_rsv->lock);
	if (block_rsv->reserved < block_rsv->size)
		num_bytes = block_rsv->size - block_rsv->reserved;
	if (block_rsv->qgroup_rsv_reserved < block_rsv->qgroup_rsv_size)
		qgroup_num_bytes = block_rsv->qgroup_rsv_size -
				   block_rsv->qgroup_rsv_reserved;
	spin_unlock(&block_rsv->lock);

	if (num_bytes == 0)
		return 0;

	ret = btrfs_qgroup_reserve_meta_prealloc(root, qgroup_num_bytes, true);
	if (ret)
		return ret;
	ret = reserve_metadata_bytes(root, block_rsv, num_bytes, flush);
	if (!ret) {
		block_rsv_add_bytes(block_rsv, num_bytes, 0);
		trace_btrfs_space_reservation(root->fs_info, "delalloc",
					      btrfs_ino(inode), num_bytes, 1);

		/* Don't forget to increase qgroup_rsv_reserved */
		spin_lock(&block_rsv->lock);
		block_rsv->qgroup_rsv_reserved += qgroup_num_bytes;
		spin_unlock(&block_rsv->lock);
	} else
		btrfs_qgroup_free_meta_prealloc(root, qgroup_num_bytes);
	return ret;
}