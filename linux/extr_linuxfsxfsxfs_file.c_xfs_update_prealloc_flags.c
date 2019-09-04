#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xfs_trans {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  di_flags; } ;
struct xfs_inode {TYPE_1__ i_d; int /*<<< orphan*/  i_mount; } ;
typedef  enum xfs_prealloc_flags { ____Placeholder_xfs_prealloc_flags } xfs_prealloc_flags ;
struct TYPE_6__ {int /*<<< orphan*/  tr_writeid; } ;
struct TYPE_5__ {int i_mode; } ;

/* Variables and functions */
 TYPE_3__* M_RES (int /*<<< orphan*/ ) ; 
 int S_ISGID ; 
 int S_ISUID ; 
 int S_IXGRP ; 
 TYPE_2__* VFS_I (struct xfs_inode*) ; 
 int /*<<< orphan*/  XFS_DIFLAG_PREALLOC ; 
 int XFS_ICHGTIME_CHG ; 
 int XFS_ICHGTIME_MOD ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_ILOG_CORE ; 
 int XFS_PREALLOC_CLEAR ; 
 int XFS_PREALLOC_INVISIBLE ; 
 int XFS_PREALLOC_SET ; 
 int XFS_PREALLOC_SYNC ; 
 int /*<<< orphan*/  xfs_ilock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_trans_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_trans**) ; 
 int xfs_trans_commit (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_trans_ichgtime (struct xfs_trans*,struct xfs_inode*,int) ; 
 int /*<<< orphan*/  xfs_trans_ijoin (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (struct xfs_trans*,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_set_sync (struct xfs_trans*) ; 

int
xfs_update_prealloc_flags(
	struct xfs_inode	*ip,
	enum xfs_prealloc_flags	flags)
{
	struct xfs_trans	*tp;
	int			error;

	error = xfs_trans_alloc(ip->i_mount, &M_RES(ip->i_mount)->tr_writeid,
			0, 0, 0, &tp);
	if (error)
		return error;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);

	if (!(flags & XFS_PREALLOC_INVISIBLE)) {
		VFS_I(ip)->i_mode &= ~S_ISUID;
		if (VFS_I(ip)->i_mode & S_IXGRP)
			VFS_I(ip)->i_mode &= ~S_ISGID;
		xfs_trans_ichgtime(tp, ip, XFS_ICHGTIME_MOD | XFS_ICHGTIME_CHG);
	}

	if (flags & XFS_PREALLOC_SET)
		ip->i_d.di_flags |= XFS_DIFLAG_PREALLOC;
	if (flags & XFS_PREALLOC_CLEAR)
		ip->i_d.di_flags &= ~XFS_DIFLAG_PREALLOC;

	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
	if (flags & XFS_PREALLOC_SYNC)
		xfs_trans_set_sync(tp);
	return xfs_trans_commit(tp);
}