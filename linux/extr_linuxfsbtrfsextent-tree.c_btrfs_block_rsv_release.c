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
struct btrfs_block_rsv {scalar_t__ space_info; } ;
struct btrfs_fs_info {struct btrfs_block_rsv global_block_rsv; } ;

/* Variables and functions */
 int /*<<< orphan*/  block_rsv_release_bytes (struct btrfs_fs_info*,struct btrfs_block_rsv*,struct btrfs_block_rsv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void btrfs_block_rsv_release(struct btrfs_fs_info *fs_info,
			     struct btrfs_block_rsv *block_rsv,
			     u64 num_bytes)
{
	struct btrfs_block_rsv *global_rsv = &fs_info->global_block_rsv;

	if (global_rsv == block_rsv ||
	    block_rsv->space_info != global_rsv->space_info)
		global_rsv = NULL;
	block_rsv_release_bytes(fs_info, block_rsv, global_rsv, num_bytes, NULL);
}