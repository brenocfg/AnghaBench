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
typedef  int /*<<< orphan*/  uint ;
struct xfs_inode {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 struct xfs_inode* XFS_I (struct inode*) ; 
 int /*<<< orphan*/  XFS_IOLOCK_EXCL ; 
 int /*<<< orphan*/  XFS_IOLOCK_SHARED ; 
 int break_layout (struct inode*,int) ; 
 int /*<<< orphan*/  xfs_ilock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,int /*<<< orphan*/ ) ; 

int
xfs_break_leased_layouts(
	struct inode		*inode,
	uint			*iolock,
	bool			*did_unlock)
{
	struct xfs_inode	*ip = XFS_I(inode);
	int			error;

	while ((error = break_layout(inode, false)) == -EWOULDBLOCK) {
		xfs_iunlock(ip, *iolock);
		*did_unlock = true;
		error = break_layout(inode, true);
		*iolock &= ~XFS_IOLOCK_SHARED;
		*iolock |= XFS_IOLOCK_EXCL;
		xfs_ilock(ip, *iolock);
	}

	return error;
}