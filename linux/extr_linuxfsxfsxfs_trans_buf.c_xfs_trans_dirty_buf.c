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
struct xfs_trans {int /*<<< orphan*/  t_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  li_flags; int /*<<< orphan*/  li_cb; } ;
struct TYPE_3__ {int /*<<< orphan*/  blf_flags; } ;
struct xfs_buf_log_item {int bli_flags; TYPE_2__ bli_item; TYPE_1__ __bli_format; int /*<<< orphan*/  bli_refcount; } ;
struct xfs_buf {int b_flags; int /*<<< orphan*/ * b_iodone; struct xfs_trans* b_transp; struct xfs_buf_log_item* b_log_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XBF_DONE ; 
 int XBF_STALE ; 
 int /*<<< orphan*/  XFS_BLF_CANCEL ; 
 int XFS_BLI_DIRTY ; 
 int XFS_BLI_LOGGED ; 
 int XFS_BLI_STALE ; 
 int /*<<< orphan*/  XFS_LI_DIRTY ; 
 int /*<<< orphan*/  XFS_TRANS_DIRTY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_buf_iodone ; 
 int /*<<< orphan*/ * xfs_buf_iodone_callbacks ; 

void
xfs_trans_dirty_buf(
	struct xfs_trans	*tp,
	struct xfs_buf		*bp)
{
	struct xfs_buf_log_item	*bip = bp->b_log_item;

	ASSERT(bp->b_transp == tp);
	ASSERT(bip != NULL);
	ASSERT(bp->b_iodone == NULL ||
	       bp->b_iodone == xfs_buf_iodone_callbacks);

	/*
	 * Mark the buffer as needing to be written out eventually,
	 * and set its iodone function to remove the buffer's buf log
	 * item from the AIL and free it when the buffer is flushed
	 * to disk.  See xfs_buf_attach_iodone() for more details
	 * on li_cb and xfs_buf_iodone_callbacks().
	 * If we end up aborting this transaction, we trap this buffer
	 * inside the b_bdstrat callback so that this won't get written to
	 * disk.
	 */
	bp->b_flags |= XBF_DONE;

	ASSERT(atomic_read(&bip->bli_refcount) > 0);
	bp->b_iodone = xfs_buf_iodone_callbacks;
	bip->bli_item.li_cb = xfs_buf_iodone;

	/*
	 * If we invalidated the buffer within this transaction, then
	 * cancel the invalidation now that we're dirtying the buffer
	 * again.  There are no races with the code in xfs_buf_item_unpin(),
	 * because we have a reference to the buffer this entire time.
	 */
	if (bip->bli_flags & XFS_BLI_STALE) {
		bip->bli_flags &= ~XFS_BLI_STALE;
		ASSERT(bp->b_flags & XBF_STALE);
		bp->b_flags &= ~XBF_STALE;
		bip->__bli_format.blf_flags &= ~XFS_BLF_CANCEL;
	}
	bip->bli_flags |= XFS_BLI_DIRTY | XFS_BLI_LOGGED;

	tp->t_flags |= XFS_TRANS_DIRTY;
	set_bit(XFS_LI_DIRTY, &bip->bli_item.li_flags);
}