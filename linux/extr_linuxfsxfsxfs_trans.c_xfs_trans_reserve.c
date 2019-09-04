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
typedef  scalar_t__ uint ;
struct xfs_trans_res {scalar_t__ tr_logres; scalar_t__ tr_logcount; int tr_logflags; } ;
struct xfs_trans {int t_flags; scalar_t__ t_blk_res; scalar_t__ t_log_res; scalar_t__ t_log_count; int /*<<< orphan*/  t_pflags; int /*<<< orphan*/  t_mountp; int /*<<< orphan*/ * t_ticket; int /*<<< orphan*/  t_rtx_res; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  PF_MEMALLOC_NOFS ; 
 int /*<<< orphan*/  XFS_TRANSACTION ; 
 int XFS_TRANS_PERM_LOG_RES ; 
 int XFS_TRANS_RESERVE ; 
 int /*<<< orphan*/  current_restore_flags_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_set_flags_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_log_done (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int xfs_log_regrant (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xfs_log_reserve (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int xfs_mod_fdblocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int xfs_mod_frextents (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
xfs_trans_reserve(
	struct xfs_trans	*tp,
	struct xfs_trans_res	*resp,
	uint			blocks,
	uint			rtextents)
{
	int		error = 0;
	bool		rsvd = (tp->t_flags & XFS_TRANS_RESERVE) != 0;

	/* Mark this thread as being in a transaction */
	current_set_flags_nested(&tp->t_pflags, PF_MEMALLOC_NOFS);

	/*
	 * Attempt to reserve the needed disk blocks by decrementing
	 * the number needed from the number available.  This will
	 * fail if the count would go below zero.
	 */
	if (blocks > 0) {
		error = xfs_mod_fdblocks(tp->t_mountp, -((int64_t)blocks), rsvd);
		if (error != 0) {
			current_restore_flags_nested(&tp->t_pflags, PF_MEMALLOC_NOFS);
			return -ENOSPC;
		}
		tp->t_blk_res += blocks;
	}

	/*
	 * Reserve the log space needed for this transaction.
	 */
	if (resp->tr_logres > 0) {
		bool	permanent = false;

		ASSERT(tp->t_log_res == 0 ||
		       tp->t_log_res == resp->tr_logres);
		ASSERT(tp->t_log_count == 0 ||
		       tp->t_log_count == resp->tr_logcount);

		if (resp->tr_logflags & XFS_TRANS_PERM_LOG_RES) {
			tp->t_flags |= XFS_TRANS_PERM_LOG_RES;
			permanent = true;
		} else {
			ASSERT(tp->t_ticket == NULL);
			ASSERT(!(tp->t_flags & XFS_TRANS_PERM_LOG_RES));
		}

		if (tp->t_ticket != NULL) {
			ASSERT(resp->tr_logflags & XFS_TRANS_PERM_LOG_RES);
			error = xfs_log_regrant(tp->t_mountp, tp->t_ticket);
		} else {
			error = xfs_log_reserve(tp->t_mountp,
						resp->tr_logres,
						resp->tr_logcount,
						&tp->t_ticket, XFS_TRANSACTION,
						permanent);
		}

		if (error)
			goto undo_blocks;

		tp->t_log_res = resp->tr_logres;
		tp->t_log_count = resp->tr_logcount;
	}

	/*
	 * Attempt to reserve the needed realtime extents by decrementing
	 * the number needed from the number available.  This will
	 * fail if the count would go below zero.
	 */
	if (rtextents > 0) {
		error = xfs_mod_frextents(tp->t_mountp, -((int64_t)rtextents));
		if (error) {
			error = -ENOSPC;
			goto undo_log;
		}
		tp->t_rtx_res += rtextents;
	}

	return 0;

	/*
	 * Error cases jump to one of these labels to undo any
	 * reservations which have already been performed.
	 */
undo_log:
	if (resp->tr_logres > 0) {
		xfs_log_done(tp->t_mountp, tp->t_ticket, NULL, false);
		tp->t_ticket = NULL;
		tp->t_log_res = 0;
		tp->t_flags &= ~XFS_TRANS_PERM_LOG_RES;
	}

undo_blocks:
	if (blocks > 0) {
		xfs_mod_fdblocks(tp->t_mountp, (int64_t)blocks, rsvd);
		tp->t_blk_res = 0;
	}

	current_restore_flags_nested(&tp->t_pflags, PF_MEMALLOC_NOFS);

	return error;
}