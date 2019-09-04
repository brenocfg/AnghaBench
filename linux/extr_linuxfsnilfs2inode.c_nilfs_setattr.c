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
struct super_block {int dummy; } ;
struct nilfs_transaction_info {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct iattr {int ia_valid; scalar_t__ ia_size; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ATTR_MODE ; 
 int ATTR_SIZE ; 
 struct inode* d_inode (struct dentry*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_dio_wait (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int nilfs_acl_chmod (struct inode*) ; 
 int /*<<< orphan*/  nilfs_transaction_abort (struct super_block*) ; 
 int nilfs_transaction_begin (struct super_block*,struct nilfs_transaction_info*,int /*<<< orphan*/ ) ; 
 int nilfs_transaction_commit (struct super_block*) ; 
 int /*<<< orphan*/  nilfs_truncate (struct inode*) ; 
 int /*<<< orphan*/  setattr_copy (struct inode*,struct iattr*) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 
 int /*<<< orphan*/  truncate_setsize (struct inode*,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

int nilfs_setattr(struct dentry *dentry, struct iattr *iattr)
{
	struct nilfs_transaction_info ti;
	struct inode *inode = d_inode(dentry);
	struct super_block *sb = inode->i_sb;
	int err;

	err = setattr_prepare(dentry, iattr);
	if (err)
		return err;

	err = nilfs_transaction_begin(sb, &ti, 0);
	if (unlikely(err))
		return err;

	if ((iattr->ia_valid & ATTR_SIZE) &&
	    iattr->ia_size != i_size_read(inode)) {
		inode_dio_wait(inode);
		truncate_setsize(inode, iattr->ia_size);
		nilfs_truncate(inode);
	}

	setattr_copy(inode, iattr);
	mark_inode_dirty(inode);

	if (iattr->ia_valid & ATTR_MODE) {
		err = nilfs_acl_chmod(inode);
		if (unlikely(err))
			goto out_err;
	}

	return nilfs_transaction_commit(sb);

out_err:
	nilfs_transaction_abort(sb);
	return err;
}