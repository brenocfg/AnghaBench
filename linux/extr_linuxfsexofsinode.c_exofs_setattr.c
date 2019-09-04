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
struct inode {int dummy; } ;
struct iattr {int ia_valid; scalar_t__ ia_size; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ATTR_SIZE ; 
 int _do_truncate (struct inode*,scalar_t__) ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  exofs_i (struct inode*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  setattr_copy (struct inode*,struct iattr*) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 
 scalar_t__ unlikely (int) ; 
 int wait_obj_created (int /*<<< orphan*/ ) ; 

int exofs_setattr(struct dentry *dentry, struct iattr *iattr)
{
	struct inode *inode = d_inode(dentry);
	int error;

	/* if we are about to modify an object, and it hasn't been
	 * created yet, wait
	 */
	error = wait_obj_created(exofs_i(inode));
	if (unlikely(error))
		return error;

	error = setattr_prepare(dentry, iattr);
	if (unlikely(error))
		return error;

	if ((iattr->ia_valid & ATTR_SIZE) &&
	    iattr->ia_size != i_size_read(inode)) {
		error = _do_truncate(inode, iattr->ia_size);
		if (unlikely(error))
			return error;
	}

	setattr_copy(inode, iattr);
	mark_inode_dirty(inode);
	return 0;
}