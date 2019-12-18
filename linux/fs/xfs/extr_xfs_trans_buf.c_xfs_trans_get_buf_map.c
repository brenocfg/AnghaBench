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
struct xfs_buf {struct xfs_buf_log_item* b_log_item; int /*<<< orphan*/  b_error; struct xfs_trans* b_transp; int /*<<< orphan*/  b_flags; } ;
typedef  struct xfs_buf xfs_buf_t ;
typedef  int /*<<< orphan*/  xfs_buf_flags_t ;
struct xfs_trans {int /*<<< orphan*/  t_mountp; } ;
struct xfs_buftarg {int dummy; } ;
struct xfs_buf_map {int dummy; } ;
struct xfs_buf_log_item {int /*<<< orphan*/  bli_recur; int /*<<< orphan*/  bli_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XBF_DONE ; 
 scalar_t__ XFS_FORCED_SHUTDOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _xfs_trans_bjoin (struct xfs_trans*,struct xfs_buf*,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_trans_get_buf (struct xfs_buf_log_item*) ; 
 int /*<<< orphan*/  trace_xfs_trans_get_buf_recur (struct xfs_buf_log_item*) ; 
 struct xfs_buf* xfs_buf_get_map (struct xfs_buftarg*,struct xfs_buf_map*,int,int /*<<< orphan*/ ) ; 
 int xfs_buf_islocked (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_stale (struct xfs_buf*) ; 
 struct xfs_buf* xfs_trans_buf_item_match (struct xfs_trans*,struct xfs_buftarg*,struct xfs_buf_map*,int) ; 

struct xfs_buf *
xfs_trans_get_buf_map(
	struct xfs_trans	*tp,
	struct xfs_buftarg	*target,
	struct xfs_buf_map	*map,
	int			nmaps,
	xfs_buf_flags_t		flags)
{
	xfs_buf_t		*bp;
	struct xfs_buf_log_item	*bip;

	if (!tp)
		return xfs_buf_get_map(target, map, nmaps, flags);

	/*
	 * If we find the buffer in the cache with this transaction
	 * pointer in its b_fsprivate2 field, then we know we already
	 * have it locked.  In this case we just increment the lock
	 * recursion count and return the buffer to the caller.
	 */
	bp = xfs_trans_buf_item_match(tp, target, map, nmaps);
	if (bp != NULL) {
		ASSERT(xfs_buf_islocked(bp));
		if (XFS_FORCED_SHUTDOWN(tp->t_mountp)) {
			xfs_buf_stale(bp);
			bp->b_flags |= XBF_DONE;
		}

		ASSERT(bp->b_transp == tp);
		bip = bp->b_log_item;
		ASSERT(bip != NULL);
		ASSERT(atomic_read(&bip->bli_refcount) > 0);
		bip->bli_recur++;
		trace_xfs_trans_get_buf_recur(bip);
		return bp;
	}

	bp = xfs_buf_get_map(target, map, nmaps, flags);
	if (bp == NULL) {
		return NULL;
	}

	ASSERT(!bp->b_error);

	_xfs_trans_bjoin(tp, bp, 1);
	trace_xfs_trans_get_buf(bp->b_log_item);
	return bp;
}