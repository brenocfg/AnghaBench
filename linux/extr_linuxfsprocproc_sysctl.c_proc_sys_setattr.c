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
struct iattr {int ia_valid; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ATTR_GID ; 
 int ATTR_MODE ; 
 int ATTR_UID ; 
 int EPERM ; 
 struct inode* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  setattr_copy (struct inode*,struct iattr*) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 

__attribute__((used)) static int proc_sys_setattr(struct dentry *dentry, struct iattr *attr)
{
	struct inode *inode = d_inode(dentry);
	int error;

	if (attr->ia_valid & (ATTR_MODE | ATTR_UID | ATTR_GID))
		return -EPERM;

	error = setattr_prepare(dentry, attr);
	if (error)
		return error;

	setattr_copy(inode, attr);
	mark_inode_dirty(inode);
	return 0;
}