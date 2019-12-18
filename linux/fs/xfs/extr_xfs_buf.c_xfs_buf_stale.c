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
struct xfs_buf {int b_state; int /*<<< orphan*/  b_lock; int /*<<< orphan*/  b_hold; int /*<<< orphan*/  b_lru; TYPE_1__* b_target; int /*<<< orphan*/  b_lru_ref; int /*<<< orphan*/  b_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  bt_lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XBF_STALE ; 
 int XFS_BSTATE_DISPOSE ; 
 int /*<<< orphan*/  _XBF_DELWRI_Q ; 
 int /*<<< orphan*/  __xfs_buf_ioacct_dec (struct xfs_buf*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ list_lru_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int xfs_buf_islocked (struct xfs_buf*) ; 

void
xfs_buf_stale(
	struct xfs_buf	*bp)
{
	ASSERT(xfs_buf_islocked(bp));

	bp->b_flags |= XBF_STALE;

	/*
	 * Clear the delwri status so that a delwri queue walker will not
	 * flush this buffer to disk now that it is stale. The delwri queue has
	 * a reference to the buffer, so this is safe to do.
	 */
	bp->b_flags &= ~_XBF_DELWRI_Q;

	/*
	 * Once the buffer is marked stale and unlocked, a subsequent lookup
	 * could reset b_flags. There is no guarantee that the buffer is
	 * unaccounted (released to LRU) before that occurs. Drop in-flight
	 * status now to preserve accounting consistency.
	 */
	spin_lock(&bp->b_lock);
	__xfs_buf_ioacct_dec(bp);

	atomic_set(&bp->b_lru_ref, 0);
	if (!(bp->b_state & XFS_BSTATE_DISPOSE) &&
	    (list_lru_del(&bp->b_target->bt_lru, &bp->b_lru)))
		atomic_dec(&bp->b_hold);

	ASSERT(atomic_read(&bp->b_hold) >= 1);
	spin_unlock(&bp->b_lock);
}