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
struct btrfs_block_rsv {int dummy; } ;
struct btrfs_fs_info {struct btrfs_block_rsv delayed_refs_rsv; } ;

/* Variables and functions */
 scalar_t__ __btrfs_block_rsv_release (struct btrfs_fs_info*,struct btrfs_block_rsv*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ btrfs_calc_insert_metadata_size (struct btrfs_fs_info*,int) ; 
 int /*<<< orphan*/  trace_btrfs_space_reservation (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

void btrfs_delayed_refs_rsv_release(struct btrfs_fs_info *fs_info, int nr)
{
	struct btrfs_block_rsv *block_rsv = &fs_info->delayed_refs_rsv;
	u64 num_bytes = btrfs_calc_insert_metadata_size(fs_info, nr);
	u64 released = 0;

	released = __btrfs_block_rsv_release(fs_info, block_rsv, num_bytes,
					     NULL);
	if (released)
		trace_btrfs_space_reservation(fs_info, "delayed_refs_rsv",
					      0, released, 0);
}