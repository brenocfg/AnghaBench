#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_2__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct f2fs_sb_info {int /*<<< orphan*/  sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
typedef  int /*<<< orphan*/  nid_t ;
struct TYPE_4__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE_EXT_IDENTIFY ; 
 int EIO ; 
 int ENOSPC ; 
 struct f2fs_sb_info* F2FS_I_SB (struct inode*) ; 
 scalar_t__ IS_DIRSYNC (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  d_instantiate_new (struct dentry*,struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 int f2fs_add_link (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  f2fs_alloc_nid_done (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_balance_fs (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_cp_error (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_dblock_aops ; 
 int /*<<< orphan*/  f2fs_file_inode_operations ; 
 int /*<<< orphan*/  f2fs_file_operations ; 
 int /*<<< orphan*/  f2fs_handle_failed_inode (struct inode*) ; 
 int /*<<< orphan*/  f2fs_is_checkpoint_ready (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  f2fs_lock_op (struct f2fs_sb_info*) ; 
 struct inode* f2fs_new_inode (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_sync_fs (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  f2fs_unlock_op (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  set_file_temperature (struct f2fs_sb_info*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f2fs_create(struct inode *dir, struct dentry *dentry, umode_t mode,
						bool excl)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(dir);
	struct inode *inode;
	nid_t ino = 0;
	int err;

	if (unlikely(f2fs_cp_error(sbi)))
		return -EIO;
	if (!f2fs_is_checkpoint_ready(sbi))
		return -ENOSPC;

	err = dquot_initialize(dir);
	if (err)
		return err;

	inode = f2fs_new_inode(dir, mode);
	if (IS_ERR(inode))
		return PTR_ERR(inode);

	if (!test_opt(sbi, DISABLE_EXT_IDENTIFY))
		set_file_temperature(sbi, inode, dentry->d_name.name);

	inode->i_op = &f2fs_file_inode_operations;
	inode->i_fop = &f2fs_file_operations;
	inode->i_mapping->a_ops = &f2fs_dblock_aops;
	ino = inode->i_ino;

	f2fs_lock_op(sbi);
	err = f2fs_add_link(dentry, inode);
	if (err)
		goto out;
	f2fs_unlock_op(sbi);

	f2fs_alloc_nid_done(sbi, ino);

	d_instantiate_new(dentry, inode);

	if (IS_DIRSYNC(dir))
		f2fs_sync_fs(sbi->sb, 1);

	f2fs_balance_fs(sbi, true);
	return 0;
out:
	f2fs_handle_failed_inode(inode);
	return err;
}