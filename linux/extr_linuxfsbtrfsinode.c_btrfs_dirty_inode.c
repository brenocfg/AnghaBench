#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ delayed_node; int /*<<< orphan*/  runtime_flags; struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_DUMMY ; 
 int ENOSPC ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_balance_delayed_items (struct btrfs_fs_info*) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*) ; 
 struct btrfs_trans_handle* btrfs_join_transaction (struct btrfs_root*) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (struct btrfs_root*,int) ; 
 int btrfs_update_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_dirty_inode(struct inode *inode)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_trans_handle *trans;
	int ret;

	if (test_bit(BTRFS_INODE_DUMMY, &BTRFS_I(inode)->runtime_flags))
		return 0;

	trans = btrfs_join_transaction(root);
	if (IS_ERR(trans))
		return PTR_ERR(trans);

	ret = btrfs_update_inode(trans, root, inode);
	if (ret && ret == -ENOSPC) {
		/* whoops, lets try again with the full transaction */
		btrfs_end_transaction(trans);
		trans = btrfs_start_transaction(root, 1);
		if (IS_ERR(trans))
			return PTR_ERR(trans);

		ret = btrfs_update_inode(trans, root, inode);
	}
	btrfs_end_transaction(trans);
	if (BTRFS_I(inode)->delayed_node)
		btrfs_balance_delayed_items(fs_info);

	return ret;
}