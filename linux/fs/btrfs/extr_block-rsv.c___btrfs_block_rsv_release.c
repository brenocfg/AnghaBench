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
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_block_rsv {scalar_t__ space_info; int /*<<< orphan*/  full; } ;
struct btrfs_fs_info {struct btrfs_block_rsv delayed_refs_rsv; struct btrfs_block_rsv global_block_rsv; } ;

/* Variables and functions */
 int /*<<< orphan*/  block_rsv_release_bytes (struct btrfs_fs_info*,struct btrfs_block_rsv*,struct btrfs_block_rsv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u64 __btrfs_block_rsv_release(struct btrfs_fs_info *fs_info,
			      struct btrfs_block_rsv *block_rsv,
			      u64 num_bytes, u64 *qgroup_to_release)
{
	struct btrfs_block_rsv *global_rsv = &fs_info->global_block_rsv;
	struct btrfs_block_rsv *delayed_rsv = &fs_info->delayed_refs_rsv;
	struct btrfs_block_rsv *target = NULL;

	/*
	 * If we are the delayed_rsv then push to the global rsv, otherwise dump
	 * into the delayed rsv if it is not full.
	 */
	if (block_rsv == delayed_rsv)
		target = global_rsv;
	else if (block_rsv != global_rsv && !delayed_rsv->full)
		target = delayed_rsv;

	if (target && block_rsv->space_info != target->space_info)
		target = NULL;

	return block_rsv_release_bytes(fs_info, block_rsv, target, num_bytes,
				       qgroup_to_release);
}