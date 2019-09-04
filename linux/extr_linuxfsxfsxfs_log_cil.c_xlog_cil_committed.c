#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfs_mount {int m_flags; } ;
struct xfs_cil_ctx {int /*<<< orphan*/  busy_extents; int /*<<< orphan*/  lv_chain; TYPE_2__* cil; int /*<<< orphan*/  committing; int /*<<< orphan*/  start_lsn; } ;
struct TYPE_4__ {int /*<<< orphan*/  xc_push_lock; int /*<<< orphan*/  xc_commit_wait; TYPE_1__* xc_log; } ;
struct TYPE_3__ {int /*<<< orphan*/  l_ailp; struct xfs_mount* l_mp; } ;

/* Variables and functions */
 int XFS_MOUNT_DISCARD ; 
 int /*<<< orphan*/  kmem_free (struct xfs_cil_ctx*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_extent_busy_clear (struct xfs_mount*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xfs_extent_busy_sort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_trans_committed_bulk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xlog_cil_free_logvec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlog_discard_busy_extents (struct xfs_mount*,struct xfs_cil_ctx*) ; 

__attribute__((used)) static void
xlog_cil_committed(
	void	*args,
	int	abort)
{
	struct xfs_cil_ctx	*ctx = args;
	struct xfs_mount	*mp = ctx->cil->xc_log->l_mp;

	xfs_trans_committed_bulk(ctx->cil->xc_log->l_ailp, ctx->lv_chain,
					ctx->start_lsn, abort);

	xfs_extent_busy_sort(&ctx->busy_extents);
	xfs_extent_busy_clear(mp, &ctx->busy_extents,
			     (mp->m_flags & XFS_MOUNT_DISCARD) && !abort);

	/*
	 * If we are aborting the commit, wake up anyone waiting on the
	 * committing list.  If we don't, then a shutdown we can leave processes
	 * waiting in xlog_cil_force_lsn() waiting on a sequence commit that
	 * will never happen because we aborted it.
	 */
	spin_lock(&ctx->cil->xc_push_lock);
	if (abort)
		wake_up_all(&ctx->cil->xc_commit_wait);
	list_del(&ctx->committing);
	spin_unlock(&ctx->cil->xc_push_lock);

	xlog_cil_free_logvec(ctx->lv_chain);

	if (!list_empty(&ctx->busy_extents))
		xlog_discard_busy_extents(mp, ctx);
	else
		kmem_free(ctx);
}