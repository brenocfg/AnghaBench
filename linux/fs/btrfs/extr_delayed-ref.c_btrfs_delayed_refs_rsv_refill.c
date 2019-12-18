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
struct btrfs_block_rsv {scalar_t__ reserved; scalar_t__ size; int /*<<< orphan*/  lock; } ;
struct btrfs_fs_info {int /*<<< orphan*/  extent_root; struct btrfs_block_rsv delayed_refs_rsv; } ;
typedef  enum btrfs_reserve_flush_enum { ____Placeholder_btrfs_reserve_flush_enum } btrfs_reserve_flush_enum ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  btrfs_block_rsv_add_bytes (struct btrfs_block_rsv*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_calc_insert_metadata_size (struct btrfs_fs_info*,int) ; 
 int btrfs_reserve_metadata_bytes (int /*<<< orphan*/ ,struct btrfs_block_rsv*,scalar_t__,int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_btrfs_space_reservation (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,scalar_t__,int) ; 

int btrfs_delayed_refs_rsv_refill(struct btrfs_fs_info *fs_info,
				  enum btrfs_reserve_flush_enum flush)
{
	struct btrfs_block_rsv *block_rsv = &fs_info->delayed_refs_rsv;
	u64 limit = btrfs_calc_insert_metadata_size(fs_info, 1);
	u64 num_bytes = 0;
	int ret = -ENOSPC;

	spin_lock(&block_rsv->lock);
	if (block_rsv->reserved < block_rsv->size) {
		num_bytes = block_rsv->size - block_rsv->reserved;
		num_bytes = min(num_bytes, limit);
	}
	spin_unlock(&block_rsv->lock);

	if (!num_bytes)
		return 0;

	ret = btrfs_reserve_metadata_bytes(fs_info->extent_root, block_rsv,
					   num_bytes, flush);
	if (ret)
		return ret;
	btrfs_block_rsv_add_bytes(block_rsv, num_bytes, 0);
	trace_btrfs_space_reservation(fs_info, "delayed_refs_rsv",
				      0, num_bytes, 1);
	return 0;
}