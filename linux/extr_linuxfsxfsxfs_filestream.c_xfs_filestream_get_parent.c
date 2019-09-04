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
struct inode {int dummy; } ;
struct dentry {int dummy; } ;

/* Variables and functions */
 struct inode* VFS_I (struct xfs_inode*) ; 
 struct xfs_inode* XFS_I (struct inode*) ; 
 struct dentry* d_find_alias (struct inode*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 struct dentry* dget_parent (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct inode* igrab (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct xfs_inode *
xfs_filestream_get_parent(
	struct xfs_inode	*ip)
{
	struct inode		*inode = VFS_I(ip), *dir = NULL;
	struct dentry		*dentry, *parent;

	dentry = d_find_alias(inode);
	if (!dentry)
		goto out;

	parent = dget_parent(dentry);
	if (!parent)
		goto out_dput;

	dir = igrab(d_inode(parent));
	dput(parent);

out_dput:
	dput(dentry);
out:
	return dir ? XFS_I(dir) : NULL;
}