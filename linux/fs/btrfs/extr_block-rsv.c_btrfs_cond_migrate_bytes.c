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
struct btrfs_block_rsv {scalar_t__ space_info; scalar_t__ size; scalar_t__ reserved; int /*<<< orphan*/  lock; scalar_t__ full; } ;
struct btrfs_fs_info {struct btrfs_block_rsv global_block_rsv; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  btrfs_block_rsv_add_bytes (struct btrfs_block_rsv*,scalar_t__,int) ; 
 scalar_t__ div_factor (scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int btrfs_cond_migrate_bytes(struct btrfs_fs_info *fs_info,
			     struct btrfs_block_rsv *dest, u64 num_bytes,
			     int min_factor)
{
	struct btrfs_block_rsv *global_rsv = &fs_info->global_block_rsv;
	u64 min_bytes;

	if (global_rsv->space_info != dest->space_info)
		return -ENOSPC;

	spin_lock(&global_rsv->lock);
	min_bytes = div_factor(global_rsv->size, min_factor);
	if (global_rsv->reserved < min_bytes + num_bytes) {
		spin_unlock(&global_rsv->lock);
		return -ENOSPC;
	}
	global_rsv->reserved -= num_bytes;
	if (global_rsv->reserved < global_rsv->size)
		global_rsv->full = 0;
	spin_unlock(&global_rsv->lock);

	btrfs_block_rsv_add_bytes(dest, num_bytes, true);
	return 0;
}