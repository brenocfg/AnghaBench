#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct btrfs_root {scalar_t__ orphan_cleanup_state; struct btrfs_fs_info* fs_info; } ;
struct btrfs_block_rsv {TYPE_1__* space_info; } ;
struct btrfs_fs_info {struct btrfs_root* chunk_root; struct btrfs_block_rsv global_block_rsv; } ;
typedef  enum btrfs_reserve_flush_enum { ____Placeholder_btrfs_reserve_flush_enum } btrfs_reserve_flush_enum ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  ENOSPC_DEBUG ; 
 scalar_t__ ORPHAN_CLEANUP_STARTED ; 
 int __reserve_metadata_bytes (struct btrfs_fs_info*,TYPE_1__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  btrfs_block_rsv_use_bytes (struct btrfs_block_rsv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_dump_space_info (struct btrfs_fs_info*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ btrfs_test_opt (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_btrfs_space_reservation (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

int btrfs_reserve_metadata_bytes(struct btrfs_root *root,
				 struct btrfs_block_rsv *block_rsv,
				 u64 orig_bytes,
				 enum btrfs_reserve_flush_enum flush)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_block_rsv *global_rsv = &fs_info->global_block_rsv;
	int ret;
	bool system_chunk = (root == fs_info->chunk_root);

	ret = __reserve_metadata_bytes(fs_info, block_rsv->space_info,
				       orig_bytes, flush, system_chunk);
	if (ret == -ENOSPC &&
	    unlikely(root->orphan_cleanup_state == ORPHAN_CLEANUP_STARTED)) {
		if (block_rsv != global_rsv &&
		    !btrfs_block_rsv_use_bytes(global_rsv, orig_bytes))
			ret = 0;
	}
	if (ret == -ENOSPC) {
		trace_btrfs_space_reservation(fs_info, "space_info:enospc",
					      block_rsv->space_info->flags,
					      orig_bytes, 1);

		if (btrfs_test_opt(fs_info, ENOSPC_DEBUG))
			btrfs_dump_space_info(fs_info, block_rsv->space_info,
					      orig_bytes, 0);
	}
	return ret;
}