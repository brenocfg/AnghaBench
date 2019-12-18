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
struct btrfs_trans_handle {int /*<<< orphan*/  delayed_ref_updates; struct btrfs_fs_info* fs_info; } ;
struct btrfs_block_rsv {int /*<<< orphan*/  lock; scalar_t__ full; int /*<<< orphan*/  size; } ;
struct btrfs_fs_info {struct btrfs_block_rsv delayed_refs_rsv; } ;

/* Variables and functions */
 scalar_t__ btrfs_calc_insert_metadata_size (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void btrfs_update_delayed_refs_rsv(struct btrfs_trans_handle *trans)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	struct btrfs_block_rsv *delayed_rsv = &fs_info->delayed_refs_rsv;
	u64 num_bytes;

	if (!trans->delayed_ref_updates)
		return;

	num_bytes = btrfs_calc_insert_metadata_size(fs_info,
						    trans->delayed_ref_updates);
	spin_lock(&delayed_rsv->lock);
	delayed_rsv->size += num_bytes;
	delayed_rsv->full = 0;
	spin_unlock(&delayed_rsv->lock);
	trans->delayed_ref_updates = 0;
}