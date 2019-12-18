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
struct super_block {int dummy; } ;
struct inode {int i_state; int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_mode; int /*<<< orphan*/ * i_op; TYPE_1__* i_mapping; int /*<<< orphan*/ * i_fop; } ;
struct f2fs_sb_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 unsigned long F2FS_META_INO (struct f2fs_sb_info*) ; 
 unsigned long F2FS_NODE_INO (struct f2fs_sb_info*) ; 
 struct f2fs_sb_info* F2FS_SB (struct super_block*) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int I_NEW ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISFIFO (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISSOCK (int /*<<< orphan*/ ) ; 
 int do_read_inode (struct inode*) ; 
 int /*<<< orphan*/  f2fs_dblock_aops ; 
 int /*<<< orphan*/  f2fs_dir_inode_operations ; 
 int /*<<< orphan*/  f2fs_dir_operations ; 
 int /*<<< orphan*/  f2fs_encrypted_symlink_inode_operations ; 
 int /*<<< orphan*/  f2fs_file_inode_operations ; 
 int /*<<< orphan*/  f2fs_file_operations ; 
 int /*<<< orphan*/  f2fs_inode_synced (struct inode*) ; 
 int /*<<< orphan*/  f2fs_meta_aops ; 
 int /*<<< orphan*/  f2fs_node_aops ; 
 int /*<<< orphan*/  f2fs_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  f2fs_special_inode_operations ; 
 int /*<<< orphan*/  f2fs_symlink_inode_operations ; 
 scalar_t__ file_is_encrypt (struct inode*) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 struct inode* iget_locked (struct super_block*,unsigned long) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_nohighmem (struct inode*) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_iget (struct inode*) ; 
 int /*<<< orphan*/  trace_f2fs_iget_exit (struct inode*,int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *f2fs_iget(struct super_block *sb, unsigned long ino)
{
	struct f2fs_sb_info *sbi = F2FS_SB(sb);
	struct inode *inode;
	int ret = 0;

	inode = iget_locked(sb, ino);
	if (!inode)
		return ERR_PTR(-ENOMEM);

	if (!(inode->i_state & I_NEW)) {
		trace_f2fs_iget(inode);
		return inode;
	}
	if (ino == F2FS_NODE_INO(sbi) || ino == F2FS_META_INO(sbi))
		goto make_now;

	ret = do_read_inode(inode);
	if (ret)
		goto bad_inode;
make_now:
	if (ino == F2FS_NODE_INO(sbi)) {
		inode->i_mapping->a_ops = &f2fs_node_aops;
		mapping_set_gfp_mask(inode->i_mapping, GFP_NOFS);
	} else if (ino == F2FS_META_INO(sbi)) {
		inode->i_mapping->a_ops = &f2fs_meta_aops;
		mapping_set_gfp_mask(inode->i_mapping, GFP_NOFS);
	} else if (S_ISREG(inode->i_mode)) {
		inode->i_op = &f2fs_file_inode_operations;
		inode->i_fop = &f2fs_file_operations;
		inode->i_mapping->a_ops = &f2fs_dblock_aops;
	} else if (S_ISDIR(inode->i_mode)) {
		inode->i_op = &f2fs_dir_inode_operations;
		inode->i_fop = &f2fs_dir_operations;
		inode->i_mapping->a_ops = &f2fs_dblock_aops;
		inode_nohighmem(inode);
	} else if (S_ISLNK(inode->i_mode)) {
		if (file_is_encrypt(inode))
			inode->i_op = &f2fs_encrypted_symlink_inode_operations;
		else
			inode->i_op = &f2fs_symlink_inode_operations;
		inode_nohighmem(inode);
		inode->i_mapping->a_ops = &f2fs_dblock_aops;
	} else if (S_ISCHR(inode->i_mode) || S_ISBLK(inode->i_mode) ||
			S_ISFIFO(inode->i_mode) || S_ISSOCK(inode->i_mode)) {
		inode->i_op = &f2fs_special_inode_operations;
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
	} else {
		ret = -EIO;
		goto bad_inode;
	}
	f2fs_set_inode_flags(inode);
	unlock_new_inode(inode);
	trace_f2fs_iget(inode);
	return inode;

bad_inode:
	f2fs_inode_synced(inode);
	iget_failed(inode);
	trace_f2fs_iget_exit(inode, ret);
	return ERR_PTR(ret);
}