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
typedef  int umode_t ;
struct xfs_inode {int dummy; } ;
struct inode {int i_mode; } ;
struct iattr {int ia_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int S_IFMT ; 
 struct inode* VFS_I (struct xfs_inode*) ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  xfs_isilocked (struct xfs_inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xfs_setattr_mode(
	struct xfs_inode	*ip,
	struct iattr		*iattr)
{
	struct inode		*inode = VFS_I(ip);
	umode_t			mode = iattr->ia_mode;

	ASSERT(xfs_isilocked(ip, XFS_ILOCK_EXCL));

	inode->i_mode &= S_IFMT;
	inode->i_mode |= mode & ~S_IFMT;
}