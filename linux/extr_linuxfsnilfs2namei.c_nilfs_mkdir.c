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
typedef  int umode_t ;
struct nilfs_transaction_info {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; TYPE_1__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  d_instantiate_new (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int nilfs_add_link (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  nilfs_aops ; 
 int /*<<< orphan*/  nilfs_dir_inode_operations ; 
 int /*<<< orphan*/  nilfs_dir_operations ; 
 int nilfs_make_empty (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  nilfs_mark_inode_dirty (struct inode*) ; 
 struct inode* nilfs_new_inode (struct inode*,int) ; 
 int /*<<< orphan*/  nilfs_transaction_abort (int /*<<< orphan*/ ) ; 
 int nilfs_transaction_begin (int /*<<< orphan*/ ,struct nilfs_transaction_info*,int) ; 
 int nilfs_transaction_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static int nilfs_mkdir(struct inode *dir, struct dentry *dentry, umode_t mode)
{
	struct inode *inode;
	struct nilfs_transaction_info ti;
	int err;

	err = nilfs_transaction_begin(dir->i_sb, &ti, 1);
	if (err)
		return err;

	inc_nlink(dir);

	inode = nilfs_new_inode(dir, S_IFDIR | mode);
	err = PTR_ERR(inode);
	if (IS_ERR(inode))
		goto out_dir;

	inode->i_op = &nilfs_dir_inode_operations;
	inode->i_fop = &nilfs_dir_operations;
	inode->i_mapping->a_ops = &nilfs_aops;

	inc_nlink(inode);

	err = nilfs_make_empty(inode, dir);
	if (err)
		goto out_fail;

	err = nilfs_add_link(dentry, inode);
	if (err)
		goto out_fail;

	nilfs_mark_inode_dirty(inode);
	d_instantiate_new(dentry, inode);
out:
	if (!err)
		err = nilfs_transaction_commit(dir->i_sb);
	else
		nilfs_transaction_abort(dir->i_sb);

	return err;

out_fail:
	drop_nlink(inode);
	drop_nlink(inode);
	nilfs_mark_inode_dirty(inode);
	unlock_new_inode(inode);
	iput(inode);
out_dir:
	drop_nlink(dir);
	nilfs_mark_inode_dirty(dir);
	goto out;
}