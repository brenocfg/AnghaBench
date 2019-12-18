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
struct btrfs_trans_handle {int /*<<< orphan*/  transid; int /*<<< orphan*/  bytes_reserved; int /*<<< orphan*/ * block_rsv; } ;
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  trans_block_rsv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_RESERVE_FLUSH_ALL ; 
 int /*<<< orphan*/  ENOSPC ; 
 struct btrfs_trans_handle* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  PTR_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  TRANS_START ; 
 int /*<<< orphan*/  btrfs_calc_insert_metadata_size (struct btrfs_fs_info*,unsigned int) ; 
 int btrfs_cond_migrate_bytes (struct btrfs_fs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (struct btrfs_root*,int /*<<< orphan*/ ) ; 
 struct btrfs_trans_handle* start_transaction (struct btrfs_root*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_btrfs_space_reservation (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

struct btrfs_trans_handle *btrfs_start_transaction_fallback_global_rsv(
					struct btrfs_root *root,
					unsigned int num_items,
					int min_factor)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_trans_handle *trans;
	u64 num_bytes;
	int ret;

	/*
	 * We have two callers: unlink and block group removal.  The
	 * former should succeed even if we will temporarily exceed
	 * quota and the latter operates on the extent root so
	 * qgroup enforcement is ignored anyway.
	 */
	trans = start_transaction(root, num_items, TRANS_START,
				  BTRFS_RESERVE_FLUSH_ALL, false);
	if (!IS_ERR(trans) || PTR_ERR(trans) != -ENOSPC)
		return trans;

	trans = btrfs_start_transaction(root, 0);
	if (IS_ERR(trans))
		return trans;

	num_bytes = btrfs_calc_insert_metadata_size(fs_info, num_items);
	ret = btrfs_cond_migrate_bytes(fs_info, &fs_info->trans_block_rsv,
				       num_bytes, min_factor);
	if (ret) {
		btrfs_end_transaction(trans);
		return ERR_PTR(ret);
	}

	trans->block_rsv = &fs_info->trans_block_rsv;
	trans->bytes_reserved = num_bytes;
	trace_btrfs_space_reservation(fs_info, "transaction",
				      trans->transid, num_bytes, 1);

	return trans;
}