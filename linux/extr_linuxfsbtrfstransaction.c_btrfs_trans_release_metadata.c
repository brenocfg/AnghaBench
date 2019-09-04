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
struct btrfs_trans_handle {int /*<<< orphan*/  bytes_reserved; int /*<<< orphan*/ * block_rsv; int /*<<< orphan*/  transid; struct btrfs_fs_info* fs_info; } ;
struct btrfs_fs_info {int /*<<< orphan*/  trans_block_rsv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  btrfs_block_rsv_release (struct btrfs_fs_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_btrfs_space_reservation (struct btrfs_fs_info*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btrfs_trans_release_metadata(struct btrfs_trans_handle *trans)

{
	struct btrfs_fs_info *fs_info = trans->fs_info;

	if (!trans->block_rsv) {
		ASSERT(!trans->bytes_reserved);
		return;
	}

	if (!trans->bytes_reserved)
		return;

	ASSERT(trans->block_rsv == &fs_info->trans_block_rsv);
	trace_btrfs_space_reservation(fs_info, "transaction",
				      trans->transid, trans->bytes_reserved, 0);
	btrfs_block_rsv_release(fs_info, trans->block_rsv,
				trans->bytes_reserved);
	trans->bytes_reserved = 0;
}