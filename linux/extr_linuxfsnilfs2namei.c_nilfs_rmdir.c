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
struct nilfs_transaction_info {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; scalar_t__ i_size; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ENOTEMPTY ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int nilfs_do_unlink (struct inode*,struct dentry*) ; 
 scalar_t__ nilfs_empty_dir (struct inode*) ; 
 int /*<<< orphan*/  nilfs_mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  nilfs_transaction_abort (int /*<<< orphan*/ ) ; 
 int nilfs_transaction_begin (int /*<<< orphan*/ ,struct nilfs_transaction_info*,int /*<<< orphan*/ ) ; 
 int nilfs_transaction_commit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode = d_inode(dentry);
	struct nilfs_transaction_info ti;
	int err;

	err = nilfs_transaction_begin(dir->i_sb, &ti, 0);
	if (err)
		return err;

	err = -ENOTEMPTY;
	if (nilfs_empty_dir(inode)) {
		err = nilfs_do_unlink(dir, dentry);
		if (!err) {
			inode->i_size = 0;
			drop_nlink(inode);
			nilfs_mark_inode_dirty(inode);
			drop_nlink(dir);
			nilfs_mark_inode_dirty(dir);
		}
	}
	if (!err)
		err = nilfs_transaction_commit(dir->i_sb);
	else
		nilfs_transaction_abort(dir->i_sb);

	return err;
}