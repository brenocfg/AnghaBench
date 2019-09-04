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
struct xfs_trans {int t_flags; int /*<<< orphan*/  t_pflags; int /*<<< orphan*/ * t_ticket; struct xfs_mount* t_mountp; } ;
struct xfs_mount {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NULLCOMMITLSN ; 
 int /*<<< orphan*/  PF_MEMALLOC_NOFS ; 
 int /*<<< orphan*/  SHUTDOWN_CORRUPT_INCORE ; 
 int /*<<< orphan*/  XFS_ERRLEVEL_LOW ; 
 int /*<<< orphan*/  XFS_ERROR_REPORT (char*,int /*<<< orphan*/ ,struct xfs_mount*) ; 
 int /*<<< orphan*/  XFS_FORCED_SHUTDOWN (struct xfs_mount*) ; 
 int XFS_TRANS_DIRTY ; 
 int XFS_TRANS_PERM_LOG_RES ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  current_restore_flags_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_trans_cancel (struct xfs_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_defer_cancel (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_force_shutdown (struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_log_done (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xfs_trans_free (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_trans_free_items (struct xfs_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_trans_unreserve_and_mod_dquots (struct xfs_trans*) ; 
 int /*<<< orphan*/  xfs_trans_unreserve_and_mod_sb (struct xfs_trans*) ; 

void
xfs_trans_cancel(
	struct xfs_trans	*tp)
{
	struct xfs_mount	*mp = tp->t_mountp;
	bool			dirty = (tp->t_flags & XFS_TRANS_DIRTY);

	trace_xfs_trans_cancel(tp, _RET_IP_);

	if (tp->t_flags & XFS_TRANS_PERM_LOG_RES)
		xfs_defer_cancel(tp);

	/*
	 * See if the caller is relying on us to shut down the
	 * filesystem.  This happens in paths where we detect
	 * corruption and decide to give up.
	 */
	if (dirty && !XFS_FORCED_SHUTDOWN(mp)) {
		XFS_ERROR_REPORT("xfs_trans_cancel", XFS_ERRLEVEL_LOW, mp);
		xfs_force_shutdown(mp, SHUTDOWN_CORRUPT_INCORE);
	}
#ifdef DEBUG
	if (!dirty && !XFS_FORCED_SHUTDOWN(mp)) {
		struct xfs_log_item *lip;

		list_for_each_entry(lip, &tp->t_items, li_trans)
			ASSERT(!(lip->li_type == XFS_LI_EFD));
	}
#endif
	xfs_trans_unreserve_and_mod_sb(tp);
	xfs_trans_unreserve_and_mod_dquots(tp);

	if (tp->t_ticket) {
		xfs_log_done(mp, tp->t_ticket, NULL, false);
		tp->t_ticket = NULL;
	}

	/* mark this thread as no longer being in a transaction */
	current_restore_flags_nested(&tp->t_pflags, PF_MEMALLOC_NOFS);

	xfs_trans_free_items(tp, NULLCOMMITLSN, dirty);
	xfs_trans_free(tp);
}