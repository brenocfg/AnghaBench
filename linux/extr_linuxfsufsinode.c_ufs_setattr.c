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
struct inode {scalar_t__ i_size; } ;
struct iattr {unsigned int ia_valid; scalar_t__ ia_size; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 unsigned int ATTR_SIZE ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  setattr_copy (struct inode*,struct iattr*) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 
 int ufs_truncate (struct inode*,scalar_t__) ; 

int ufs_setattr(struct dentry *dentry, struct iattr *attr)
{
	struct inode *inode = d_inode(dentry);
	unsigned int ia_valid = attr->ia_valid;
	int error;

	error = setattr_prepare(dentry, attr);
	if (error)
		return error;

	if (ia_valid & ATTR_SIZE && attr->ia_size != inode->i_size) {
		error = ufs_truncate(inode, attr->ia_size);
		if (error)
			return error;
	}

	setattr_copy(inode, attr);
	mark_inode_dirty(inode);
	return 0;
}