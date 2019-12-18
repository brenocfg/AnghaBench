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
struct inode {int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; } ;
struct iattr {int ia_valid; int /*<<< orphan*/  ia_mtime; int /*<<< orphan*/  ia_ctime; int /*<<< orphan*/  ia_atime; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ATTR_ATIME ; 
 int ATTR_CTIME ; 
 int ATTR_MTIME ; 
 struct inode* VFS_I (struct xfs_inode*) ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  xfs_isilocked (struct xfs_inode*,int /*<<< orphan*/ ) ; 

void
xfs_setattr_time(
	struct xfs_inode	*ip,
	struct iattr		*iattr)
{
	struct inode		*inode = VFS_I(ip);

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));

	if (iattr->ia_valid & ATTR_ATIME)
		inode->i_atime = iattr->ia_atime;
	if (iattr->ia_valid & ATTR_CTIME)
		inode->i_ctime = iattr->ia_ctime;
	if (iattr->ia_valid & ATTR_MTIME)
		inode->i_mtime = iattr->ia_mtime;
}