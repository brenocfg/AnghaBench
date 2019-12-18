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
typedef  int /*<<< orphan*/  xfs_attr_sf_hdr_t ;
struct xfs_trans_res {int /*<<< orphan*/  tr_logflags; int /*<<< orphan*/  tr_logcount; scalar_t__ tr_logres; } ;
struct xfs_mount {int m_flags; } ;
struct xfs_inode {struct xfs_mount* i_mount; } ;
struct xfs_da_args {unsigned char* value; int valuelen; int op_flags; int total; scalar_t__ trans; int /*<<< orphan*/  namelen; } ;
struct TYPE_5__ {int tr_logres; } ;
struct TYPE_4__ {scalar_t__ tr_logres; } ;
struct TYPE_6__ {TYPE_2__ tr_attrsetrt; TYPE_1__ tr_attrsetm; } ;

/* Variables and functions */
 int ATTR_KERNOTIME ; 
 int ATTR_ROOT ; 
 int EIO ; 
 TYPE_3__* M_RES (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_ATTRSET_LOG_COUNT ; 
 int XFS_ATTR_SF_ENTSIZE_BYNAME (int /*<<< orphan*/ ,int) ; 
 int XFS_DA_OP_ADDNAME ; 
 int XFS_DA_OP_OKNOENT ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_ICHGTIME_CHG ; 
 scalar_t__ XFS_IFORK_Q (struct xfs_inode*) ; 
 int /*<<< orphan*/  XFS_ILOCK_EXCL ; 
 int /*<<< orphan*/  XFS_ILOG_CORE ; 
 int XFS_MOUNT_WSYNC ; 
 int XFS_QMOPT_FORCE_RES ; 
 int XFS_QMOPT_RES_REGBLKS ; 
 int /*<<< orphan*/  XFS_STATS_INC (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_TRANS_PERM_LOG_RES ; 
 int /*<<< orphan*/  XFS_TRANS_RESERVE ; 
 int xfs_attr_args_init (struct xfs_da_args*,struct xfs_inode*,unsigned char const*,int) ; 
 int xfs_attr_calc_size (struct xfs_da_args*,int*) ; 
 int xfs_attr_set_args (struct xfs_da_args*) ; 
 int xfs_bmap_add_attrfork (struct xfs_inode*,int,int) ; 
 int /*<<< orphan*/  xfs_ilock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_iunlock (struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_qm_dqattach (struct xfs_inode*) ; 
 int xfs_trans_alloc (struct xfs_mount*,struct xfs_trans_res*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  xfs_trans_cancel (scalar_t__) ; 
 int xfs_trans_commit (scalar_t__) ; 
 int /*<<< orphan*/  xfs_trans_ichgtime (scalar_t__,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_ijoin (scalar_t__,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_log_inode (scalar_t__,struct xfs_inode*,int /*<<< orphan*/ ) ; 
 int xfs_trans_reserve_quota_nblks (scalar_t__,struct xfs_inode*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_trans_set_sync (scalar_t__) ; 
 int /*<<< orphan*/  xs_attr_set ; 

int
xfs_attr_set(
	struct xfs_inode	*dp,
	const unsigned char	*name,
	unsigned char		*value,
	int			valuelen,
	int			flags)
{
	struct xfs_mount	*mp = dp->i_mount;
	struct xfs_da_args	args;
	struct xfs_trans_res	tres;
	int			rsvd = (flags & ATTR_ROOT) != 0;
	int			error, local;

	XFS_STATS_INC(mp, xs_attr_set);

	if (XFS_FORCED_SHUTDOWN(dp->i_mount))
		return -EIO;

	error = xfs_attr_args_init(&args, dp, name, flags);
	if (error)
		return error;

	args.value = value;
	args.valuelen = valuelen;
	args.op_flags = XFS_DA_OP_ADDNAME | XFS_DA_OP_OKNOENT;
	args.total = xfs_attr_calc_size(&args, &local);

	error = xfs_qm_dqattach(dp);
	if (error)
		return error;

	/*
	 * If the inode doesn't have an attribute fork, add one.
	 * (inode must not be locked when we call this routine)
	 */
	if (XFS_IFORK_Q(dp) == 0) {
		int sf_size = sizeof(xfs_attr_sf_hdr_t) +
			XFS_ATTR_SF_ENTSIZE_BYNAME(args.namelen, valuelen);

		error = xfs_bmap_add_attrfork(dp, sf_size, rsvd);
		if (error)
			return error;
	}

	tres.tr_logres = M_RES(mp)->tr_attrsetm.tr_logres +
			 M_RES(mp)->tr_attrsetrt.tr_logres * args.total;
	tres.tr_logcount = XFS_ATTRSET_LOG_COUNT;
	tres.tr_logflags = XFS_TRANS_PERM_LOG_RES;

	/*
	 * Root fork attributes can use reserved data blocks for this
	 * operation if necessary
	 */
	error = xfs_trans_alloc(mp, &tres, args.total, 0,
			rsvd ? XFS_TRANS_RESERVE : 0, &args.trans);
	if (error)
		return error;

	xfs_ilock(dp, XFS_ILOCK_EXCL);
	error = xfs_trans_reserve_quota_nblks(args.trans, dp, args.total, 0,
				rsvd ? XFS_QMOPT_RES_REGBLKS | XFS_QMOPT_FORCE_RES :
				       XFS_QMOPT_RES_REGBLKS);
	if (error)
		goto out_trans_cancel;

	xfs_trans_ijoin(args.trans, dp, 0);
	error = xfs_attr_set_args(&args);
	if (error)
		goto out_trans_cancel;
	if (!args.trans) {
		/* shortform attribute has already been committed */
		goto out_unlock;
	}

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
out_unlock:
	xfs_iunlock(dp, XFS_ILOCK_EXCL);
	return error;

out_trans_cancel:
	if (args.trans)
		xfs_trans_cancel(args.trans);
	goto out_unlock;
}