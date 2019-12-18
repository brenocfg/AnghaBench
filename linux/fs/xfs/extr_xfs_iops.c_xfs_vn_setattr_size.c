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
struct xfs_inode {int dummy; } ;
struct iattr {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct xfs_inode* XFS_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  trace_xfs_setattr (struct xfs_inode*) ; 
 int xfs_setattr_size (struct xfs_inode*,struct iattr*) ; 
 int xfs_vn_change_ok (struct dentry*,struct iattr*) ; 

int
xfs_vn_setattr_size(
	struct dentry		*dentry,
	struct iattr		*iattr)
{
	struct xfs_inode	*ip = XFS_I(d_inode(dentry));
	int error;

	trace_xfs_setattr(ip);

	error = xfs_vn_change_ok(dentry, iattr);
	if (error)
		return error;
	return xfs_setattr_size(ip, iattr);
}