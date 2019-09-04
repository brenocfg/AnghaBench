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
struct xfs_mount {int m_flags; } ;
struct iattr {int dummy; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {struct xfs_mount* i_mount; } ;

/* Variables and functions */
 int EIO ; 
 int EROFS ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 TYPE_1__* XFS_I (int /*<<< orphan*/ ) ; 
 int XFS_MOUNT_RDONLY ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int setattr_prepare (struct dentry*,struct iattr*) ; 

__attribute__((used)) static int
xfs_vn_change_ok(
	struct dentry	*dentry,
	struct iattr	*iattr)
{
	struct xfs_mount	*mp = XFS_I(d_inode(dentry))->i_mount;

	if (mp->m_flags & XFS_MOUNT_RDONLY)
		return -EROFS;

	if (XFS_FORCED_SHUTDOWN(mp))
		return -EIO;

	return setattr_prepare(dentry, iattr);
}