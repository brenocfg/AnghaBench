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
struct xfs_trans {int dummy; } ;
struct xfs_buf_log_item {int /*<<< orphan*/  bli_flags; int /*<<< orphan*/  bli_refcount; } ;
struct xfs_buf {struct xfs_trans* b_transp; struct xfs_buf_log_item* b_log_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_BLI_ORDERED ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_buf_item_ordered (struct xfs_buf_log_item*) ; 
 scalar_t__ xfs_buf_item_dirty_format (struct xfs_buf_log_item*) ; 
 int /*<<< orphan*/  xfs_trans_dirty_buf (struct xfs_trans*,struct xfs_buf*) ; 

bool
xfs_trans_ordered_buf(
	struct xfs_trans	*tp,
	struct xfs_buf		*bp)
{
	struct xfs_buf_log_item	*bip = bp->b_log_item;

	ASSERT(bp->b_transp == tp);
	ASSERT(bip != NULL);
	ASSERT(atomic_read(&bip->bli_refcount) > 0);

	if (xfs_buf_item_dirty_format(bip))
		return false;

	bip->bli_flags |= XFS_BLI_ORDERED;
	trace_xfs_buf_item_ordered(bip);

	/*
	 * We don't log a dirty range of an ordered buffer but it still needs
	 * to be marked dirty and that it has been logged.
	 */
	xfs_trans_dirty_buf(tp, bp);
	return true;
}