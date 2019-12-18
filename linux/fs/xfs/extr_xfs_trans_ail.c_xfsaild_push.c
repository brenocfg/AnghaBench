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
typedef  int /*<<< orphan*/  xfs_mount_t ;
typedef  void* xfs_lsn_t ;
struct xfs_log_item {void* li_lsn; } ;
struct xfs_ail_cursor {int dummy; } ;
struct xfs_ail {void* ail_last_pushed_lsn; scalar_t__ ail_log_flush; int /*<<< orphan*/  ail_buf_list; int /*<<< orphan*/  ail_lock; void* ail_target_prev; void* ail_target; int /*<<< orphan*/ * ail_mount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
#define  XFS_ITEM_FLUSHING 131 
#define  XFS_ITEM_LOCKED 130 
#define  XFS_ITEM_PINNED 129 
#define  XFS_ITEM_SUCCESS 128 
 int /*<<< orphan*/  XFS_LOG_SYNC ; 
 scalar_t__ XFS_LSN_CMP (void*,void*) ; 
 int /*<<< orphan*/  XFS_STATS_INC (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty_careful (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_ail_flushing (struct xfs_log_item*) ; 
 int /*<<< orphan*/  trace_xfs_ail_locked (struct xfs_log_item*) ; 
 int /*<<< orphan*/  trace_xfs_ail_pinned (struct xfs_log_item*) ; 
 int /*<<< orphan*/  trace_xfs_ail_push (struct xfs_log_item*) ; 
 scalar_t__ xfs_ail_min_lsn (struct xfs_ail*) ; 
 scalar_t__ xfs_buf_delwri_submit_nowait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_log_force (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_ail_cursor_done (struct xfs_ail_cursor*) ; 
 struct xfs_log_item* xfs_trans_ail_cursor_first (struct xfs_ail*,struct xfs_ail_cursor*,void*) ; 
 struct xfs_log_item* xfs_trans_ail_cursor_next (struct xfs_ail*,struct xfs_ail_cursor*) ; 
 int xfsaild_push_item (struct xfs_ail*,struct xfs_log_item*) ; 
 int /*<<< orphan*/  xs_push_ail ; 
 int /*<<< orphan*/  xs_push_ail_flush ; 
 int /*<<< orphan*/  xs_push_ail_flushing ; 
 int /*<<< orphan*/  xs_push_ail_locked ; 
 int /*<<< orphan*/  xs_push_ail_pinned ; 
 int /*<<< orphan*/  xs_push_ail_success ; 

__attribute__((used)) static long
xfsaild_push(
	struct xfs_ail		*ailp)
{
	xfs_mount_t		*mp = ailp->ail_mount;
	struct xfs_ail_cursor	cur;
	struct xfs_log_item	*lip;
	xfs_lsn_t		lsn;
	xfs_lsn_t		target;
	long			tout;
	int			stuck = 0;
	int			flushing = 0;
	int			count = 0;

	/*
	 * If we encountered pinned items or did not finish writing out all
	 * buffers the last time we ran, force the log first and wait for it
	 * before pushing again.
	 */
	if (ailp->ail_log_flush && ailp->ail_last_pushed_lsn == 0 &&
	    (!list_empty_careful(&ailp->ail_buf_list) ||
	     xfs_ail_min_lsn(ailp))) {
		ailp->ail_log_flush = 0;

		XFS_STATS_INC(mp, xs_push_ail_flush);
		xfs_log_force(mp, XFS_LOG_SYNC);
	}

	spin_lock(&ailp->ail_lock);

	/* barrier matches the ail_target update in xfs_ail_push() */
	smp_rmb();
	target = ailp->ail_target;
	ailp->ail_target_prev = target;

	lip = xfs_trans_ail_cursor_first(ailp, &cur, ailp->ail_last_pushed_lsn);
	if (!lip) {
		/*
		 * If the AIL is empty or our push has reached the end we are
		 * done now.
		 */
		xfs_trans_ail_cursor_done(&cur);
		spin_unlock(&ailp->ail_lock);
		goto out_done;
	}

	XFS_STATS_INC(mp, xs_push_ail);

	lsn = lip->li_lsn;
	while ((XFS_LSN_CMP(lip->li_lsn, target) <= 0)) {
		int	lock_result;

		/*
		 * Note that iop_push may unlock and reacquire the AIL lock.  We
		 * rely on the AIL cursor implementation to be able to deal with
		 * the dropped lock.
		 */
		lock_result = xfsaild_push_item(ailp, lip);
		switch (lock_result) {
		case XFS_ITEM_SUCCESS:
			XFS_STATS_INC(mp, xs_push_ail_success);
			trace_xfs_ail_push(lip);

			ailp->ail_last_pushed_lsn = lsn;
			break;

		case XFS_ITEM_FLUSHING:
			/*
			 * The item or its backing buffer is already beeing
			 * flushed.  The typical reason for that is that an
			 * inode buffer is locked because we already pushed the
			 * updates to it as part of inode clustering.
			 *
			 * We do not want to to stop flushing just because lots
			 * of items are already beeing flushed, but we need to
			 * re-try the flushing relatively soon if most of the
			 * AIL is beeing flushed.
			 */
			XFS_STATS_INC(mp, xs_push_ail_flushing);
			trace_xfs_ail_flushing(lip);

			flushing++;
			ailp->ail_last_pushed_lsn = lsn;
			break;

		case XFS_ITEM_PINNED:
			XFS_STATS_INC(mp, xs_push_ail_pinned);
			trace_xfs_ail_pinned(lip);

			stuck++;
			ailp->ail_log_flush++;
			break;
		case XFS_ITEM_LOCKED:
			XFS_STATS_INC(mp, xs_push_ail_locked);
			trace_xfs_ail_locked(lip);

			stuck++;
			break;
		default:
			ASSERT(0);
			break;
		}

		count++;

		/*
		 * Are there too many items we can't do anything with?
		 *
		 * If we we are skipping too many items because we can't flush
		 * them or they are already being flushed, we back off and
		 * given them time to complete whatever operation is being
		 * done. i.e. remove pressure from the AIL while we can't make
		 * progress so traversals don't slow down further inserts and
		 * removals to/from the AIL.
		 *
		 * The value of 100 is an arbitrary magic number based on
		 * observation.
		 */
		if (stuck > 100)
			break;

		lip = xfs_trans_ail_cursor_next(ailp, &cur);
		if (lip == NULL)
			break;
		lsn = lip->li_lsn;
	}
	xfs_trans_ail_cursor_done(&cur);
	spin_unlock(&ailp->ail_lock);

	if (xfs_buf_delwri_submit_nowait(&ailp->ail_buf_list))
		ailp->ail_log_flush++;

	if (!count || XFS_LSN_CMP(lsn, target) >= 0) {
out_done:
		/*
		 * We reached the target or the AIL is empty, so wait a bit
		 * longer for I/O to complete and remove pushed items from the
		 * AIL before we start the next scan from the start of the AIL.
		 */
		tout = 50;
		ailp->ail_last_pushed_lsn = 0;
	} else if (((stuck + flushing) * 100) / count > 90) {
		/*
		 * Either there is a lot of contention on the AIL or we are
		 * stuck due to operations in progress. "Stuck" in this case
		 * is defined as >90% of the items we tried to push were stuck.
		 *
		 * Backoff a bit more to allow some I/O to complete before
		 * restarting from the start of the AIL. This prevents us from
		 * spinning on the same items, and if they are pinned will all
		 * the restart to issue a log force to unpin the stuck items.
		 */
		tout = 20;
		ailp->ail_last_pushed_lsn = 0;
	} else {
		/*
		 * Assume we have more work to do in a short while.
		 */
		tout = 10;
	}

	return tout;
}