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
typedef  int xfs_lsn_t ;
struct xfs_trans {int t_flags; int /*<<< orphan*/  t_pflags; int /*<<< orphan*/ * t_ticket; int /*<<< orphan*/  t_dfops; struct xfs_mount* t_mountp; } ;
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  PF_MEMALLOC_NOFS ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_LOG_SYNC ; 
 int /*<<< orphan*/  XFS_STATS_INC (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int XFS_TRANS_DIRTY ; 
 int XFS_TRANS_PERM_LOG_RES ; 
 int XFS_TRANS_SB_DIRTY ; 
 int XFS_TRANS_SYNC ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  current_restore_flags_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_trans_commit (struct xfs_trans*,int /*<<< orphan*/ ) ; 
 int xfs_defer_finish_noroll (struct xfs_trans**) ; 
 int /*<<< orphan*/  xfs_log_commit_cil (struct xfs_mount*,struct xfs_trans*,int*,int) ; 
 int xfs_log_done (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int xfs_log_force_lsn (struct xfs_mount*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_apply_dquot_deltas (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_trans_apply_sb_deltas (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_trans_free (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_trans_free_items (struct xfs_trans*,int) ; 
 int /*<<< orphan*/  xfs_trans_unreserve_and_mod_dquots (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_trans_unreserve_and_mod_sb (struct xfs_trans*) ; 
 int /*<<< orphan*/  xs_trans_async ; 
 int /*<<< orphan*/  xs_trans_empty ; 
 int /*<<< orphan*/  xs_trans_sync ; 

__attribute__((used)) static int
__xfs_trans_commit(
	struct xfs_trans	*tp,
	bool			regrant)
{
	struct xfs_mount	*mp = tp->t_mountp;
	xfs_lsn_t		commit_lsn = -1;
	int			error = 0;
	int			sync = tp->t_flags & XFS_TRANS_SYNC;

	trace_xfs_trans_commit(tp, _RET_IP_);

	/*
	 * Finish deferred items on final commit. Only permanent transactions
	 * should ever have deferred ops.
	 */
	WARN_ON_ONCE(!list_empty(&tp->t_dfops) &&
		     !(tp->t_flags & XFS_TRANS_PERM_LOG_RES));
	if (!regrant && (tp->t_flags & XFS_TRANS_PERM_LOG_RES)) {
		error = xfs_defer_finish_noroll(&tp);
		if (error)
			goto out_unreserve;
	}

	/*
	 * If there is nothing to be logged by the transaction,
	 * then unlock all of the items associated with the
	 * transaction and free the transaction structure.
	 * Also make sure to return any reserved blocks to
	 * the free pool.
	 */
	if (!(tp->t_flags & XFS_TRANS_DIRTY))
		goto out_unreserve;

	if (XFS_FORCED_SHUTDOWN(mp)) {
		error = -EIO;
		goto out_unreserve;
	}

	ASSERT(tp->t_ticket != NULL);

	/*
	 * If we need to update the superblock, then do it now.
	 */
	if (tp->t_flags & XFS_TRANS_SB_DIRTY)
		xfs_trans_apply_sb_deltas(tp);
	xfs_trans_apply_dquot_deltas(tp);

	xfs_log_commit_cil(mp, tp, &commit_lsn, regrant);

	current_restore_flags_nested(&tp->t_pflags, PF_MEMALLOC_NOFS);
	xfs_trans_free(tp);

	/*
	 * If the transaction needs to be synchronous, then force the
	 * log out now and wait for it.
	 */
	if (sync) {
		error = xfs_log_force_lsn(mp, commit_lsn, XFS_LOG_SYNC, NULL);
		XFS_STATS_INC(mp, xs_trans_sync);
	} else {
		XFS_STATS_INC(mp, xs_trans_async);
	}

	return error;

out_unreserve:
	xfs_trans_unreserve_and_mod_sb(tp);

	/*
	 * It is indeed possible for the transaction to be not dirty but
	 * the dqinfo portion to be.  All that means is that we have some
	 * (non-persistent) quota reservations that need to be unreserved.
	 */
	xfs_trans_unreserve_and_mod_dquots(tp);
	if (tp->t_ticket) {
		commit_lsn = xfs_log_done(mp, tp->t_ticket, NULL, regrant);
		if (commit_lsn == -1 && !error)
			error = -EIO;
		tp->t_ticket = NULL;
	}
	current_restore_flags_nested(&tp->t_pflags, PF_MEMALLOC_NOFS);
	xfs_trans_free_items(tp, !!error);
	xfs_trans_free(tp);

	XFS_STATS_INC(mp, xs_trans_empty);
	return error;
}