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
struct xfs_buf {int b_flags; int /*<<< orphan*/  b_list; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int _XBF_DELWRI_Q ; 
 int /*<<< orphan*/  list_move (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submit_list ; 
 int /*<<< orphan*/  trace_xfs_buf_delwri_pushbuf (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_delwri_submit_buffers (int /*<<< orphan*/ *,struct list_head*) ; 
 int xfs_buf_iowait (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_lock (struct xfs_buf*) ; 
 int /*<<< orphan*/  xfs_buf_unlock (struct xfs_buf*) ; 

int
xfs_buf_delwri_pushbuf(
	struct xfs_buf		*bp,
	struct list_head	*buffer_list)
{
	LIST_HEAD		(submit_list);
	int			error;

	ASSERT(bp->b_flags & _XBF_DELWRI_Q);

	trace_xfs_buf_delwri_pushbuf(bp, _RET_IP_);

	/*
	 * Isolate the buffer to a new local list so we can submit it for I/O
	 * independently from the rest of the original list.
	 */
	xfs_buf_lock(bp);
	list_move(&bp->b_list, &submit_list);
	xfs_buf_unlock(bp);

	/*
	 * Delwri submission clears the DELWRI_Q buffer flag and returns with
	 * the buffer on the wait list with the original reference. Rather than
	 * bounce the buffer from a local wait list back to the original list
	 * after I/O completion, reuse the original list as the wait list.
	 */
	xfs_buf_delwri_submit_buffers(&submit_list, buffer_list);

	/*
	 * The buffer is now locked, under I/O and wait listed on the original
	 * delwri queue. Wait for I/O completion, restore the DELWRI_Q flag and
	 * return with the buffer unlocked and on the original queue.
	 */
	error = xfs_buf_iowait(bp);
	bp->b_flags |= _XBF_DELWRI_Q;
	xfs_buf_unlock(bp);

	return error;
}