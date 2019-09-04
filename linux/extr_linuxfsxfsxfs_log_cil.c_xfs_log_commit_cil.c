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
typedef  int /*<<< orphan*/  xfs_lsn_t ;
struct xlog {struct xfs_cil* l_cilp; } ;
struct xfs_trans {int /*<<< orphan*/ * t_ticket; } ;
struct xfs_mount {struct xlog* m_log; } ;
struct xfs_cil {int /*<<< orphan*/  xc_ctx_lock; TYPE_1__* xc_ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  sequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_log_done (struct xfs_mount*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xfs_trans_free_items (struct xfs_trans*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_trans_unreserve_and_mod_sb (struct xfs_trans*) ; 
 int /*<<< orphan*/  xlog_cil_alloc_shadow_bufs (struct xlog*,struct xfs_trans*) ; 
 int /*<<< orphan*/  xlog_cil_insert_items (struct xlog*,struct xfs_trans*) ; 
 int /*<<< orphan*/  xlog_cil_push_background (struct xlog*) ; 

void
xfs_log_commit_cil(
	struct xfs_mount	*mp,
	struct xfs_trans	*tp,
	xfs_lsn_t		*commit_lsn,
	bool			regrant)
{
	struct xlog		*log = mp->m_log;
	struct xfs_cil		*cil = log->l_cilp;
	xfs_lsn_t		xc_commit_lsn;

	/*
	 * Do all necessary memory allocation before we lock the CIL.
	 * This ensures the allocation does not deadlock with a CIL
	 * push in memory reclaim (e.g. from kswapd).
	 */
	xlog_cil_alloc_shadow_bufs(log, tp);

	/* lock out background commit */
	down_read(&cil->xc_ctx_lock);

	xlog_cil_insert_items(log, tp);

	xc_commit_lsn = cil->xc_ctx->sequence;
	if (commit_lsn)
		*commit_lsn = xc_commit_lsn;

	xfs_log_done(mp, tp->t_ticket, NULL, regrant);
	tp->t_ticket = NULL;
	xfs_trans_unreserve_and_mod_sb(tp);

	/*
	 * Once all the items of the transaction have been copied to the CIL,
	 * the items can be unlocked and freed.
	 *
	 * This needs to be done before we drop the CIL context lock because we
	 * have to update state in the log items and unlock them before they go
	 * to disk. If we don't, then the CIL checkpoint can race with us and
	 * we can run checkpoint completion before we've updated and unlocked
	 * the log items. This affects (at least) processing of stale buffers,
	 * inodes and EFIs.
	 */
	xfs_trans_free_items(tp, xc_commit_lsn, false);

	xlog_cil_push_background(log);

	up_read(&cil->xc_ctx_lock);
}