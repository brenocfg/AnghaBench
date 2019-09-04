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
struct xfs_mount {int m_flags; } ;
struct TYPE_4__ {scalar_t__ di_aformat; } ;
struct xfs_inode {TYPE_2__* i_afp; TYPE_1__ i_d; struct xfs_mount* i_mount; } ;
struct xfs_da_args {scalar_t__ trans; int /*<<< orphan*/  op_flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  tr_attrrm; } ;
struct TYPE_5__ {int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ATTR_KERNOTIME ; 
 int ATTR_ROOT ; 
 int EIO ; 
 int ENOATTR ; 
 TYPE_3__* M_RES (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_ATTRRM_SPACE_RES (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_ATTR_FORK ; 
 int /*<<< orphan*/  XFS_DA_OP_OKNOENT ; 
 scalar_t__ XFS_DINODE_FMT_LOCAL ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_ICHGTIME_CHG ; 
 int XFS_IFINLINE ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_ILOG_CORE ; 
 int XFS_MOUNT_WSYNC ; 
 int /*<<< orphan*/  XFS_STATS_INC (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_TRANS_RESERVE ; 
 int xfs_attr_args_init (struct xfs_da_args*,struct xfs_inode*,unsigned char const*,int) ; 
 int xfs_attr_leaf_removename (struct xfs_da_args*) ; 
 int xfs_attr_node_removename (struct xfs_da_args*) ; 
 int xfs_attr_shortform_remove (struct xfs_da_args*) ; 
 scalar_t__ xfs_bmap_one_block (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_ilock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_inode_hasattr (struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_qm_dqattach (struct xfs_inode*) ; 
 int xfs_trans_alloc (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  xfs_trans_cancel (scalar_t__) ; 
 int xfs_trans_commit (scalar_t__) ; 
 int /*<<< orphan*/  xfs_trans_ichgtime (scalar_t__,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_ijoin (scalar_t__,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (scalar_t__,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_set_sync (scalar_t__) ; 
 int /*<<< orphan*/  xs_attr_remove ; 

int
xfs_attr_remove(
	struct xfs_inode	*dp,
	const unsigned char	*name,
	int			flags)
{
	struct xfs_mount	*mp = dp->i_mount;
	struct xfs_da_args	args;
	int			error;

	XFS_STATS_INC(mp, xs_attr_remove);

	if (XFS_FORCED_SHUTDOWN(dp->i_mount))
		return -EIO;

	error = xfs_attr_args_init(&args, dp, name, flags);
	if (error)
		return error;

	/*
	 * we have no control over the attribute names that userspace passes us
	 * to remove, so we have to allow the name lookup prior to attribute
	 * removal to fail.
	 */
	args.op_flags = XFS_DA_OP_OKNOENT;

	error = xfs_qm_dqattach(dp);
	if (error)
		return error;

	/*
	 * Root fork attributes can use reserved data blocks for this
	 * operation if necessary
	 */
	error = xfs_trans_alloc(mp, &M_RES(mp)->tr_attrrm,
			XFS_ATTRRM_SPACE_RES(mp), 0,
			(flags & ATTR_ROOT) ? XFS_TRANS_RESERVE : 0,
			&args.trans);
	if (error)
		return error;

	xfs_ilock(dp, XFS_ILOCK_EXCL);
	/*
	 * No need to make quota reservations here. We expect to release some
	 * blocks not allocate in the common case.
	 */
	xfs_trans_ijoin(args.trans, dp, 0);

	if (!xfs_inode_hasattr(dp)) {
		error = -ENOATTR;
	} else if (dp->i_d.di_aformat == XFS_DINODE_FMT_LOCAL) {
		ASSERT(dp->i_afp->if_flags & XFS_IFINLINE);
		error = xfs_attr_shortform_remove(&args);
	} else if (xfs_bmap_one_block(dp, XFS_ATTR_FORK)) {
		error = xfs_attr_leaf_removename(&args);
	} else {
		error = xfs_attr_node_removename(&args);
	}

	if (error)
		goto out;

	/*
	 * If this is a synchronous mount, make sure that the
	 * transaction goes to disk before returning to the user.
	 */
	if (mp->m_flags & XFS_MOUNT_WSYNC)
		xfs_trans_set_sync(args.trans);

	if ((flags & ATTR_KERNOTIME) == 0)
		xfs_trans_ichgtime(args.trans, dp, XFS_ICHGTIME_CHG);

	/*
	 * Commit the last in the sequence of transactions.
	 */
	xfs_trans_log_inode(args.trans, dp, XFS_ILOG_CORE);
	error = xfs_trans_commit(args.trans);
	xfs_iunlock(dp, XFS_ILOCK_EXCL);

	return error;

out:
	if (args.trans)
		xfs_trans_cancel(args.trans);
	xfs_iunlock(dp, XFS_ILOCK_EXCL);
	return error;
}