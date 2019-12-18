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
struct file {int dummy; } ;

/* Variables and functions */
 struct xfs_inode* XFS_I (struct inode*) ; 
 int /*<<< orphan*/  XFS_MMAPLOCK_EXCL ; 
 struct inode* file_inode (struct file*) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,int /*<<< orphan*/ ) ; 

void
xfs_reflink_remap_unlock(
	struct file		*file_in,
	struct file		*file_out)
{
	struct inode		*inode_in = file_inode(file_in);
	struct xfs_inode	*src = XFS_I(inode_in);
	struct inode		*inode_out = file_inode(file_out);
	struct xfs_inode	*dest = XFS_I(inode_out);
	bool			same_inode = (inode_in == inode_out);

	xfs_iunlock(dest, XFS_MMAPLOCK_EXCL);
	if (!same_inode)
		xfs_iunlock(src, XFS_MMAPLOCK_EXCL);
	inode_unlock(inode_out);
	if (!same_inode)
		inode_unlock(inode_in);
}