#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int t_blk_res_used; int t_blk_res; int t_rtx_res_used; int t_rtx_res; int t_flags; int /*<<< orphan*/  t_rextslog_delta; int /*<<< orphan*/  t_rextents_delta; int /*<<< orphan*/  t_rblocks_delta; int /*<<< orphan*/  t_rbmblocks_delta; int /*<<< orphan*/  t_rextsize_delta; int /*<<< orphan*/  t_imaxpct_delta; int /*<<< orphan*/  t_agcount_delta; int /*<<< orphan*/  t_dblocks_delta; int /*<<< orphan*/  t_res_frextents_delta; int /*<<< orphan*/  t_frextents_delta; int /*<<< orphan*/  t_res_fdblocks_delta; int /*<<< orphan*/  t_fdblocks_delta; int /*<<< orphan*/  t_ifree_delta; int /*<<< orphan*/  t_icount_delta; TYPE_2__* t_mountp; } ;
typedef  TYPE_1__ xfs_trans_t ;
struct TYPE_6__ {int /*<<< orphan*/  m_sb; } ;
typedef  TYPE_2__ xfs_mount_t ;
typedef  int uint32_t ;
typedef  int uint ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  SHUTDOWN_CORRUPT_INCORE ; 
 int XFS_TRANS_DIRTY ; 
#define  XFS_TRANS_SB_AGCOUNT 141 
#define  XFS_TRANS_SB_DBLOCKS 140 
 int XFS_TRANS_SB_DIRTY ; 
#define  XFS_TRANS_SB_FDBLOCKS 139 
#define  XFS_TRANS_SB_FREXTENTS 138 
#define  XFS_TRANS_SB_ICOUNT 137 
#define  XFS_TRANS_SB_IFREE 136 
#define  XFS_TRANS_SB_IMAXPCT 135 
#define  XFS_TRANS_SB_RBLOCKS 134 
#define  XFS_TRANS_SB_RBMBLOCKS 133 
#define  XFS_TRANS_SB_RES_FDBLOCKS 132 
#define  XFS_TRANS_SB_RES_FREXTENTS 131 
#define  XFS_TRANS_SB_REXTENTS 130 
#define  XFS_TRANS_SB_REXTSIZE 129 
#define  XFS_TRANS_SB_REXTSLOG 128 
 int /*<<< orphan*/  xfs_force_shutdown (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_sb_version_haslazysbcount (int /*<<< orphan*/ *) ; 

void
xfs_trans_mod_sb(
	xfs_trans_t	*tp,
	uint		field,
	int64_t		delta)
{
	uint32_t	flags = (XFS_TRANS_DIRTY|XFS_TRANS_SB_DIRTY);
	xfs_mount_t	*mp = tp->t_mountp;

	switch (field) {
	case XFS_TRANS_SB_ICOUNT:
		tp->t_icount_delta += delta;
		if (xfs_sb_version_haslazysbcount(&mp->m_sb))
			flags &= ~XFS_TRANS_SB_DIRTY;
		break;
	case XFS_TRANS_SB_IFREE:
		tp->t_ifree_delta += delta;
		if (xfs_sb_version_haslazysbcount(&mp->m_sb))
			flags &= ~XFS_TRANS_SB_DIRTY;
		break;
	case XFS_TRANS_SB_FDBLOCKS:
		/*
		 * Track the number of blocks allocated in the transaction.
		 * Make sure it does not exceed the number reserved. If so,
		 * shutdown as this can lead to accounting inconsistency.
		 */
		if (delta < 0) {
			tp->t_blk_res_used += (uint)-delta;
			if (tp->t_blk_res_used > tp->t_blk_res)
				xfs_force_shutdown(mp, SHUTDOWN_CORRUPT_INCORE);
		}
		tp->t_fdblocks_delta += delta;
		if (xfs_sb_version_haslazysbcount(&mp->m_sb))
			flags &= ~XFS_TRANS_SB_DIRTY;
		break;
	case XFS_TRANS_SB_RES_FDBLOCKS:
		/*
		 * The allocation has already been applied to the
		 * in-core superblock's counter.  This should only
		 * be applied to the on-disk superblock.
		 */
		tp->t_res_fdblocks_delta += delta;
		if (xfs_sb_version_haslazysbcount(&mp->m_sb))
			flags &= ~XFS_TRANS_SB_DIRTY;
		break;
	case XFS_TRANS_SB_FREXTENTS:
		/*
		 * Track the number of blocks allocated in the
		 * transaction.  Make sure it does not exceed the
		 * number reserved.
		 */
		if (delta < 0) {
			tp->t_rtx_res_used += (uint)-delta;
			ASSERT(tp->t_rtx_res_used <= tp->t_rtx_res);
		}
		tp->t_frextents_delta += delta;
		break;
	case XFS_TRANS_SB_RES_FREXTENTS:
		/*
		 * The allocation has already been applied to the
		 * in-core superblock's counter.  This should only
		 * be applied to the on-disk superblock.
		 */
		ASSERT(delta < 0);
		tp->t_res_frextents_delta += delta;
		break;
	case XFS_TRANS_SB_DBLOCKS:
		ASSERT(delta > 0);
		tp->t_dblocks_delta += delta;
		break;
	case XFS_TRANS_SB_AGCOUNT:
		ASSERT(delta > 0);
		tp->t_agcount_delta += delta;
		break;
	case XFS_TRANS_SB_IMAXPCT:
		tp->t_imaxpct_delta += delta;
		break;
	case XFS_TRANS_SB_REXTSIZE:
		tp->t_rextsize_delta += delta;
		break;
	case XFS_TRANS_SB_RBMBLOCKS:
		tp->t_rbmblocks_delta += delta;
		break;
	case XFS_TRANS_SB_RBLOCKS:
		tp->t_rblocks_delta += delta;
		break;
	case XFS_TRANS_SB_REXTENTS:
		tp->t_rextents_delta += delta;
		break;
	case XFS_TRANS_SB_REXTSLOG:
		tp->t_rextslog_delta += delta;
		break;
	default:
		ASSERT(0);
		return;
	}

	tp->t_flags |= flags;
}