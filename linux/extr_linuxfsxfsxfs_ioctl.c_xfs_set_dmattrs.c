#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
typedef  int /*<<< orphan*/  xfs_mount_t ;
struct TYPE_8__ {int /*<<< orphan*/  di_dmstate; int /*<<< orphan*/  di_dmevmask; } ;
struct TYPE_9__ {TYPE_1__ i_d; int /*<<< orphan*/ * i_mount; } ;
typedef  TYPE_2__ xfs_inode_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  uint ;
struct TYPE_10__ {int /*<<< orphan*/  tr_ichange; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int EIO ; 
 int EPERM ; 
 TYPE_7__* M_RES (int /*<<< orphan*/ *) ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_ILOG_CORE ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ilock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int xfs_trans_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int xfs_trans_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_ijoin (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

int
xfs_set_dmattrs(
	xfs_inode_t     *ip,
	uint		evmask,
	uint16_t	state)
{
	xfs_mount_t	*mp = ip->i_mount;
	xfs_trans_t	*tp;
	int		error;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	if (XFS_FORCED_SHUTDOWN(mp))
		return -EIO;

	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_ichange, 0, 0, 0, &tp);
	if (error)
		return error;

	xfs_ilock(ip, XFS_ILOCK_EXCL);
	xfs_trans_ijoin(tp, ip, XFS_ILOCK_EXCL);

	ip->i_d.di_dmevmask = evmask;
	ip->i_d.di_dmstate  = state;

	xfs_trans_log_inode(tp, ip, XFS_ILOG_CORE);
	error = xfs_trans_commit(tp);

	return error;
}