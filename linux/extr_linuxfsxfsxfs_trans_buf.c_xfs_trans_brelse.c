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
struct xfs_trans {int dummy; } ;
struct TYPE_2__ {scalar_t__ li_type; int /*<<< orphan*/  li_flags; } ;
struct xfs_buf_log_item {scalar_t__ bli_recur; int bli_flags; TYPE_1__ bli_item; int /*<<< orphan*/  bli_refcount; } ;
struct xfs_buf {struct xfs_trans* b_transp; struct xfs_buf_log_item* b_log_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XFS_BLI_HOLD ; 
 int XFS_BLI_LOGGED ; 
 int XFS_BLI_STALE ; 
 scalar_t__ XFS_LI_BUF ; 
 int /*<<< orphan*/  XFS_LI_DIRTY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_trans_brelse (struct xfs_buf_log_item*) ; 
 int /*<<< orphan*/  xfs_buf_item_put (struct xfs_buf_log_item*) ; 
 int /*<<< orphan*/  xfs_buf_relse (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_trans_del_item (TYPE_1__*) ; 

void
xfs_trans_brelse(
	struct xfs_trans	*tp,
	struct xfs_buf		*bp)
{
	struct xfs_buf_log_item	*bip = bp->b_log_item;

	ASSERT(bp->b_transp == tp);

	if (!tp) {
		xfs_buf_relse(bp);
		return;
	}

	trace_xfs_trans_brelse(bip);
	ASSERT(bip->bli_item.li_type == XFS_LI_BUF);
	ASSERT(atomic_read(&bip->bli_refcount) > 0);

	/*
	 * If the release is for a recursive lookup, then decrement the count
	 * and return.
	 */
	if (bip->bli_recur > 0) {
		bip->bli_recur--;
		return;
	}

	/*
	 * If the buffer is invalidated or dirty in this transaction, we can't
	 * release it until we commit.
	 */
	if (test_bit(XFS_LI_DIRTY, &bip->bli_item.li_flags))
		return;
	if (bip->bli_flags & XFS_BLI_STALE)
		return;

	/*
	 * Unlink the log item from the transaction and clear the hold flag, if
	 * set. We wouldn't want the next user of the buffer to get confused.
	 */
	ASSERT(!(bip->bli_flags & XFS_BLI_LOGGED));
	xfs_trans_del_item(&bip->bli_item);
	bip->bli_flags &= ~XFS_BLI_HOLD;

	/* drop the reference to the bli */
	xfs_buf_item_put(bip);

	bp->b_transp = NULL;
	xfs_buf_relse(bp);
}