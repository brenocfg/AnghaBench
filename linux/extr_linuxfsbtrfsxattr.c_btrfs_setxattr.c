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
struct inode {int /*<<< orphan*/  i_ctime; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  runtime_flags; struct btrfs_root* root; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_COPY_EVERYTHING ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EROFS ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*) ; 
 scalar_t__ btrfs_root_readonly (struct btrfs_root*) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (struct btrfs_root*,int) ; 
 int btrfs_update_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int do_setxattr (struct btrfs_trans_handle*,struct inode*,char const*,void const*,size_t,int) ; 
 int /*<<< orphan*/  inode_inc_iversion (struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrfs_setxattr(struct btrfs_trans_handle *trans,
		     struct inode *inode, const char *name,
		     const void *value, size_t size, int flags)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;
	int ret;

	if (btrfs_root_readonly(root))
		return -EROFS;

	if (trans)
		return do_setxattr(trans, inode, name, value, size, flags);

	trans = btrfs_start_transaction(root, 2);
	if (IS_ERR(trans))
		return PTR_ERR(trans);

	ret = do_setxattr(trans, inode, name, value, size, flags);
	if (ret)
		goto out;

	inode_inc_iversion(inode);
	inode->i_ctime = current_time(inode);
	set_bit(BTRFS_INODE_COPY_EVERYTHING, &BTRFS_I(inode)->runtime_flags);
	ret = btrfs_update_inode(trans, root, inode);
	BUG_ON(ret);
out:
	btrfs_end_transaction(trans);
	return ret;
}