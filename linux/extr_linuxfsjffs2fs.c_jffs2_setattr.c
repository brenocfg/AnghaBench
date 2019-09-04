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
struct inode {int /*<<< orphan*/  i_mode; } ;
struct iattr {int ia_valid; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 int ATTR_MODE ; 
 struct inode* d_inode (struct dentry*) ; 
 int jffs2_do_setattr (struct inode*,struct iattr*) ; 
 int posix_acl_chmod (struct inode*,int /*<<< orphan*/ ) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 

int jffs2_setattr(struct dentry *dentry, struct iattr *iattr)
{
	struct inode *inode = d_inode(dentry);
	int rc;

	rc = setattr_prepare(dentry, iattr);
	if (rc)
		return rc;

	rc = jffs2_do_setattr(inode, iattr);
	if (!rc && (iattr->ia_valid & ATTR_MODE))
		rc = posix_acl_chmod(inode, inode->i_mode);

	return rc;
}