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
struct xfs_buf {int b_flags; int /*<<< orphan*/  b_list; int /*<<< orphan*/  b_hold; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XBF_READ ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int _XBF_DELWRI_Q ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_buf_delwri_queue (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_buf_delwri_queued (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int xfs_buf_islocked (struct xfs_buf*) ; 

bool
xfs_buf_delwri_queue(
	struct xfs_buf		*bp,
	struct list_head	*list)
{
	ASSERT(xfs_buf_islocked(bp));
	ASSERT(!(bp->b_flags & XBF_READ));

	/*
	 * If the buffer is already marked delwri it already is queued up
	 * by someone else for imediate writeout.  Just ignore it in that
	 * case.
	 */
	if (bp->b_flags & _XBF_DELWRI_Q) {
		trace_xfs_buf_delwri_queued(bp, _RET_IP_);
		return false;
	}

	trace_xfs_buf_delwri_queue(bp, _RET_IP_);

	/*
	 * If a buffer gets written out synchronously or marked stale while it
	 * is on a delwri list we lazily remove it. To do this, the other party
	 * clears the  _XBF_DELWRI_Q flag but otherwise leaves the buffer alone.
	 * It remains referenced and on the list.  In a rare corner case it
	 * might get readded to a delwri list after the synchronous writeout, in
	 * which case we need just need to re-add the flag here.
	 */
	bp->b_flags |= _XBF_DELWRI_Q;
	if (list_empty(&bp->b_list)) {
		atomic_inc(&bp->b_hold);
		list_add_tail(&bp->b_list, list);
	}

	return true;
}