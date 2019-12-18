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
struct xfs_trans {TYPE_1__* t_mountp; } ;
struct TYPE_2__ {int m_flags; } ;

/* Variables and functions */
 int XFS_MOUNT_DIRSYNC ; 
 int XFS_MOUNT_WSYNC ; 
 int xfs_trans_commit (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_trans_set_sync (struct xfs_trans*) ; 

__attribute__((used)) static int
xfs_finish_rename(
	struct xfs_trans	*tp)
{
	/*
	 * If this is a synchronous mount, make sure that the rename transaction
	 * goes to disk before returning to the user.
	 */
	if (tp->t_mountp->m_flags & (XFS_MOUNT_WSYNC|XFS_MOUNT_DIRSYNC))
		xfs_trans_set_sync(tp);

	return xfs_trans_commit(tp);
}