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
struct xfs_trans {int t_flags; scalar_t__ t_blk_res; scalar_t__ t_fdblocks_delta; scalar_t__ t_rtx_res; scalar_t__ t_frextents_delta; int t_icount_delta; int t_ifree_delta; int t_dblocks_delta; int t_agcount_delta; int t_rextsize_delta; int t_rbmblocks_delta; int t_rblocks_delta; int t_rextents_delta; int /*<<< orphan*/  t_imaxpct_delta; int /*<<< orphan*/  t_rextslog_delta; struct xfs_mount* t_mountp; } ;
struct TYPE_2__ {int /*<<< orphan*/  sb_frextents; int /*<<< orphan*/  sb_dblocks; int /*<<< orphan*/  sb_agcount; int /*<<< orphan*/  sb_imax_pct; int /*<<< orphan*/  sb_rextsize; int /*<<< orphan*/  sb_rbmblocks; int /*<<< orphan*/  sb_rblocks; int /*<<< orphan*/  sb_rextents; int /*<<< orphan*/  sb_rextslog; } ;
struct xfs_mount {int /*<<< orphan*/  m_sb_lock; TYPE_1__ m_sb; } ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XFS_TRANS_RESERVE ; 
 int XFS_TRANS_SB_DIRTY ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int xfs_mod_fdblocks (struct xfs_mount*,int,int) ; 
 int xfs_mod_icount (struct xfs_mount*,int) ; 
 int xfs_mod_ifree (struct xfs_mount*,int) ; 
 int xfs_sb_mod32 (int /*<<< orphan*/ *,int) ; 
 int xfs_sb_mod64 (int /*<<< orphan*/ *,int) ; 
 int xfs_sb_mod8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xfs_sb_version_haslazysbcount (TYPE_1__*) ; 

void
xfs_trans_unreserve_and_mod_sb(
	struct xfs_trans	*tp)
{
	struct xfs_mount	*mp = tp->t_mountp;
	bool			rsvd = (tp->t_flags & XFS_TRANS_RESERVE) != 0;
	int64_t			blkdelta = 0;
	int64_t			rtxdelta = 0;
	int64_t			idelta = 0;
	int64_t			ifreedelta = 0;
	int			error;

	/* calculate deltas */
	if (tp->t_blk_res > 0)
		blkdelta = tp->t_blk_res;
	if ((tp->t_fdblocks_delta != 0) &&
	    (xfs_sb_version_haslazysbcount(&mp->m_sb) ||
	     (tp->t_flags & XFS_TRANS_SB_DIRTY)))
	        blkdelta += tp->t_fdblocks_delta;

	if (tp->t_rtx_res > 0)
		rtxdelta = tp->t_rtx_res;
	if ((tp->t_frextents_delta != 0) &&
	    (tp->t_flags & XFS_TRANS_SB_DIRTY))
		rtxdelta += tp->t_frextents_delta;

	if (xfs_sb_version_haslazysbcount(&mp->m_sb) ||
	     (tp->t_flags & XFS_TRANS_SB_DIRTY)) {
		idelta = tp->t_icount_delta;
		ifreedelta = tp->t_ifree_delta;
	}

	/* apply the per-cpu counters */
	if (blkdelta) {
		error = xfs_mod_fdblocks(mp, blkdelta, rsvd);
		if (error)
			goto out;
	}

	if (idelta) {
		error = xfs_mod_icount(mp, idelta);
		if (error)
			goto out_undo_fdblocks;
	}

	if (ifreedelta) {
		error = xfs_mod_ifree(mp, ifreedelta);
		if (error)
			goto out_undo_icount;
	}

	if (rtxdelta == 0 && !(tp->t_flags & XFS_TRANS_SB_DIRTY))
		return;

	/* apply remaining deltas */
	spin_lock(&mp->m_sb_lock);
	if (rtxdelta) {
		error = xfs_sb_mod64(&mp->m_sb.sb_frextents, rtxdelta);
		if (error)
			goto out_undo_ifree;
	}

	if (tp->t_dblocks_delta != 0) {
		error = xfs_sb_mod64(&mp->m_sb.sb_dblocks, tp->t_dblocks_delta);
		if (error)
			goto out_undo_frextents;
	}
	if (tp->t_agcount_delta != 0) {
		error = xfs_sb_mod32(&mp->m_sb.sb_agcount, tp->t_agcount_delta);
		if (error)
			goto out_undo_dblocks;
	}
	if (tp->t_imaxpct_delta != 0) {
		error = xfs_sb_mod8(&mp->m_sb.sb_imax_pct, tp->t_imaxpct_delta);
		if (error)
			goto out_undo_agcount;
	}
	if (tp->t_rextsize_delta != 0) {
		error = xfs_sb_mod32(&mp->m_sb.sb_rextsize,
				     tp->t_rextsize_delta);
		if (error)
			goto out_undo_imaxpct;
	}
	if (tp->t_rbmblocks_delta != 0) {
		error = xfs_sb_mod32(&mp->m_sb.sb_rbmblocks,
				     tp->t_rbmblocks_delta);
		if (error)
			goto out_undo_rextsize;
	}
	if (tp->t_rblocks_delta != 0) {
		error = xfs_sb_mod64(&mp->m_sb.sb_rblocks, tp->t_rblocks_delta);
		if (error)
			goto out_undo_rbmblocks;
	}
	if (tp->t_rextents_delta != 0) {
		error = xfs_sb_mod64(&mp->m_sb.sb_rextents,
				     tp->t_rextents_delta);
		if (error)
			goto out_undo_rblocks;
	}
	if (tp->t_rextslog_delta != 0) {
		error = xfs_sb_mod8(&mp->m_sb.sb_rextslog,
				     tp->t_rextslog_delta);
		if (error)
			goto out_undo_rextents;
	}
	spin_unlock(&mp->m_sb_lock);
	return;

out_undo_rextents:
	if (tp->t_rextents_delta)
		xfs_sb_mod64(&mp->m_sb.sb_rextents, -tp->t_rextents_delta);
out_undo_rblocks:
	if (tp->t_rblocks_delta)
		xfs_sb_mod64(&mp->m_sb.sb_rblocks, -tp->t_rblocks_delta);
out_undo_rbmblocks:
	if (tp->t_rbmblocks_delta)
		xfs_sb_mod32(&mp->m_sb.sb_rbmblocks, -tp->t_rbmblocks_delta);
out_undo_rextsize:
	if (tp->t_rextsize_delta)
		xfs_sb_mod32(&mp->m_sb.sb_rextsize, -tp->t_rextsize_delta);
out_undo_imaxpct:
	if (tp->t_rextsize_delta)
		xfs_sb_mod8(&mp->m_sb.sb_imax_pct, -tp->t_imaxpct_delta);
out_undo_agcount:
	if (tp->t_agcount_delta)
		xfs_sb_mod32(&mp->m_sb.sb_agcount, -tp->t_agcount_delta);
out_undo_dblocks:
	if (tp->t_dblocks_delta)
		xfs_sb_mod64(&mp->m_sb.sb_dblocks, -tp->t_dblocks_delta);
out_undo_frextents:
	if (rtxdelta)
		xfs_sb_mod64(&mp->m_sb.sb_frextents, -rtxdelta);
out_undo_ifree:
	spin_unlock(&mp->m_sb_lock);
	if (ifreedelta)
		xfs_mod_ifree(mp, -ifreedelta);
out_undo_icount:
	if (idelta)
		xfs_mod_icount(mp, -idelta);
out_undo_fdblocks:
	if (blkdelta)
		xfs_mod_fdblocks(mp, -blkdelta, rsvd);
out:
	ASSERT(error == 0);
	return;
}