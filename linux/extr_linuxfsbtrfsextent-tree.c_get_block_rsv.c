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
struct btrfs_trans_handle {struct btrfs_block_rsv* block_rsv; scalar_t__ adding_csums; } ;
struct btrfs_root {struct btrfs_block_rsv* block_rsv; int /*<<< orphan*/  state; struct btrfs_fs_info* fs_info; } ;
struct btrfs_block_rsv {int dummy; } ;
struct btrfs_fs_info {struct btrfs_block_rsv empty_block_rsv; struct btrfs_root const* uuid_root; struct btrfs_root const* csum_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_ROOT_REF_COWS ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct btrfs_block_rsv *get_block_rsv(
					const struct btrfs_trans_handle *trans,
					const struct btrfs_root *root)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_block_rsv *block_rsv = NULL;

	if (test_bit(BTRFS_ROOT_REF_COWS, &root->state) ||
	    (root == fs_info->csum_root && trans->adding_csums) ||
	    (root == fs_info->uuid_root))
		block_rsv = trans->block_rsv;

	if (!block_rsv)
		block_rsv = root->block_rsv;

	if (!block_rsv)
		block_rsv = &fs_info->empty_block_rsv;

	return block_rsv;
}