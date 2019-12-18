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
struct xfs_log_vec {struct xfs_log_item* lv_item; struct xfs_log_vec* lv_next; } ;
struct xfs_log_item {TYPE_1__* li_ops; int /*<<< orphan*/  li_lsn; int /*<<< orphan*/  li_flags; } ;
struct xfs_ail_cursor {int dummy; } ;
struct xfs_ail {int /*<<< orphan*/  ail_lock; int /*<<< orphan*/  ail_mount; } ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  (* iop_unpin ) (struct xfs_log_item*,int) ;int /*<<< orphan*/  (* iop_committed ) (struct xfs_log_item*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* iop_release ) (struct xfs_log_item*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int LOG_ITEM_BATCH_SIZE ; 
 int /*<<< orphan*/  XFS_FORCED_SHUTDOWN (int /*<<< orphan*/ ) ; 
 int XFS_ITEM_RELEASE_WHEN_COMMITTED ; 
 int /*<<< orphan*/  XFS_LI_ABORTED ; 
 scalar_t__ XFS_LSN_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct xfs_log_item*) ; 
 int /*<<< orphan*/  stub2 (struct xfs_log_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct xfs_log_item*,int) ; 
 int /*<<< orphan*/  stub4 (struct xfs_log_item*,int) ; 
 int /*<<< orphan*/  xfs_log_item_batch_insert (struct xfs_ail*,struct xfs_ail_cursor*,struct xfs_log_item**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_ail_cursor_done (struct xfs_ail_cursor*) ; 
 int /*<<< orphan*/  xfs_trans_ail_cursor_last (struct xfs_ail*,struct xfs_ail_cursor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_ail_update (struct xfs_ail*,struct xfs_log_item*,int /*<<< orphan*/ ) ; 

void
xfs_trans_committed_bulk(
	struct xfs_ail		*ailp,
	struct xfs_log_vec	*log_vector,
	xfs_lsn_t		commit_lsn,
	bool			aborted)
{
#define LOG_ITEM_BATCH_SIZE	32
	struct xfs_log_item	*log_items[LOG_ITEM_BATCH_SIZE];
	struct xfs_log_vec	*lv;
	struct xfs_ail_cursor	cur;
	int			i = 0;

	spin_lock(&ailp->ail_lock);
	xfs_trans_ail_cursor_last(ailp, &cur, commit_lsn);
	spin_unlock(&ailp->ail_lock);

	/* unpin all the log items */
	for (lv = log_vector; lv; lv = lv->lv_next ) {
		struct xfs_log_item	*lip = lv->lv_item;
		xfs_lsn_t		item_lsn;

		if (aborted)
			set_bit(XFS_LI_ABORTED, &lip->li_flags);

		if (lip->li_ops->flags & XFS_ITEM_RELEASE_WHEN_COMMITTED) {
			lip->li_ops->iop_release(lip);
			continue;
		}

		if (lip->li_ops->iop_committed)
			item_lsn = lip->li_ops->iop_committed(lip, commit_lsn);
		else
			item_lsn = commit_lsn;

		/* item_lsn of -1 means the item needs no further processing */
		if (XFS_LSN_CMP(item_lsn, (xfs_lsn_t)-1) == 0)
			continue;

		/*
		 * if we are aborting the operation, no point in inserting the
		 * object into the AIL as we are in a shutdown situation.
		 */
		if (aborted) {
			ASSERT(XFS_FORCED_SHUTDOWN(ailp->ail_mount));
			if (lip->li_ops->iop_unpin)
				lip->li_ops->iop_unpin(lip, 1);
			continue;
		}

		if (item_lsn != commit_lsn) {

			/*
			 * Not a bulk update option due to unusual item_lsn.
			 * Push into AIL immediately, rechecking the lsn once
			 * we have the ail lock. Then unpin the item. This does
			 * not affect the AIL cursor the bulk insert path is
			 * using.
			 */
			spin_lock(&ailp->ail_lock);
			if (XFS_LSN_CMP(item_lsn, lip->li_lsn) > 0)
				xfs_trans_ail_update(ailp, lip, item_lsn);
			else
				spin_unlock(&ailp->ail_lock);
			if (lip->li_ops->iop_unpin)
				lip->li_ops->iop_unpin(lip, 0);
			continue;
		}

		/* Item is a candidate for bulk AIL insert.  */
		log_items[i++] = lv->lv_item;
		if (i >= LOG_ITEM_BATCH_SIZE) {
			xfs_log_item_batch_insert(ailp, &cur, log_items,
					LOG_ITEM_BATCH_SIZE, commit_lsn);
			i = 0;
		}
	}

	/* make sure we insert the remainder! */
	if (i)
		xfs_log_item_batch_insert(ailp, &cur, log_items, i, commit_lsn);

	spin_lock(&ailp->ail_lock);
	xfs_trans_ail_cursor_done(&cur);
	spin_unlock(&ailp->ail_lock);
}