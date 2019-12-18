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
struct inode {int i_blocks; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mode; } ;
struct dnode_of_data {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  F2FS_I_SB (struct inode*) ; 
 int /*<<< orphan*/  LOOKUP_NODE ; 
 int /*<<< orphan*/  SBI_NEED_FSCK ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int f2fs_cp_error (int /*<<< orphan*/ ) ; 
 int f2fs_get_dnode_of_data (struct dnode_of_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_put_dnode (struct dnode_of_data*) ; 
 int /*<<< orphan*/  f2fs_truncate_data_blocks_range (struct dnode_of_data*,int) ; 
 int f2fs_truncate_xattr_node (struct inode*) ; 
 int /*<<< orphan*/  f2fs_warn (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  set_new_dnode (struct dnode_of_data*,struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_sbi_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int truncate_node (struct dnode_of_data*) ; 
 scalar_t__ unlikely (int) ; 

int f2fs_remove_inode_page(struct inode *inode)
{
	struct dnode_of_data dn;
	int err;

	set_new_dnode(&dn, inode, NULL, NULL, inode->i_ino);
	err = f2fs_get_dnode_of_data(&dn, 0, LOOKUP_NODE);
	if (err)
		return err;

	err = f2fs_truncate_xattr_node(inode);
	if (err) {
		f2fs_put_dnode(&dn);
		return err;
	}

	/* remove potential inline_data blocks */
	if (S_ISREG(inode->i_mode) || S_ISDIR(inode->i_mode) ||
				S_ISLNK(inode->i_mode))
		f2fs_truncate_data_blocks_range(&dn, 1);

	/* 0 is possible, after f2fs_new_inode() has failed */
	if (unlikely(f2fs_cp_error(F2FS_I_SB(inode)))) {
		f2fs_put_dnode(&dn);
		return -EIO;
	}

	if (unlikely(inode->i_blocks != 0 && inode->i_blocks != 8)) {
		f2fs_warn(F2FS_I_SB(inode), "Inconsistent i_blocks, ino:%lu, iblocks:%llu",
			  inode->i_ino, (unsigned long long)inode->i_blocks);
		set_sbi_flag(F2FS_I_SB(inode), SBI_NEED_FSCK);
	}

	/* will put inode & node pages */
	err = truncate_node(&dn);
	if (err) {
		f2fs_put_dnode(&dn);
		return err;
	}
	return 0;
}