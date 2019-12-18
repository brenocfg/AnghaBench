#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int b_flags; int b_state; int /*<<< orphan*/  b_lock; int /*<<< orphan*/  b_rhash_head; int /*<<< orphan*/  b_lru; TYPE_1__* b_target; int /*<<< orphan*/  b_hold; int /*<<< orphan*/  b_lru_ref; struct xfs_perag* b_pag; } ;
typedef  TYPE_2__ xfs_buf_t ;
struct xfs_perag {int /*<<< orphan*/  pag_buf_lock; int /*<<< orphan*/  pag_buf_hash; } ;
struct TYPE_8__ {int /*<<< orphan*/  bt_lru; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XBF_STALE ; 
 int XFS_BSTATE_DISPOSE ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int _XBF_DELWRI_Q ; 
 int /*<<< orphan*/  __xfs_buf_ioacct_dec (TYPE_2__*) ; 
 int atomic_dec_and_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int list_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ list_lru_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_lru_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_remove_fast (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_buf_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_free (TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_buf_hash_params ; 
 int /*<<< orphan*/  xfs_buf_ioacct_dec (TYPE_2__*) ; 
 int /*<<< orphan*/  xfs_perag_put (struct xfs_perag*) ; 

void
xfs_buf_rele(
	xfs_buf_t		*bp)
{
	struct xfs_perag	*pag = bp->b_pag;
	bool			release;
	bool			freebuf = false;

	trace_xfs_buf_rele(bp, _RET_IP_);

	if (!pag) {
		ASSERT(list_empty(&bp->b_lru));
		if (atomic_dec_and_test(&bp->b_hold)) {
			xfs_buf_ioacct_dec(bp);
			xfs_buf_free(bp);
		}
		return;
	}

	ASSERT(atomic_read(&bp->b_hold) > 0);

	/*
	 * We grab the b_lock here first to serialise racing xfs_buf_rele()
	 * calls. The pag_buf_lock being taken on the last reference only
	 * serialises against racing lookups in xfs_buf_find(). IOWs, the second
	 * to last reference we drop here is not serialised against the last
	 * reference until we take bp->b_lock. Hence if we don't grab b_lock
	 * first, the last "release" reference can win the race to the lock and
	 * free the buffer before the second-to-last reference is processed,
	 * leading to a use-after-free scenario.
	 */
	spin_lock(&bp->b_lock);
	release = atomic_dec_and_lock(&bp->b_hold, &pag->pag_buf_lock);
	if (!release) {
		/*
		 * Drop the in-flight state if the buffer is already on the LRU
		 * and it holds the only reference. This is racy because we
		 * haven't acquired the pag lock, but the use of _XBF_IN_FLIGHT
		 * ensures the decrement occurs only once per-buf.
		 */
		if ((atomic_read(&bp->b_hold) == 1) && !list_empty(&bp->b_lru))
			__xfs_buf_ioacct_dec(bp);
		goto out_unlock;
	}

	/* the last reference has been dropped ... */
	__xfs_buf_ioacct_dec(bp);
	if (!(bp->b_flags & XBF_STALE) && atomic_read(&bp->b_lru_ref)) {
		/*
		 * If the buffer is added to the LRU take a new reference to the
		 * buffer for the LRU and clear the (now stale) dispose list
		 * state flag
		 */
		if (list_lru_add(&bp->b_target->bt_lru, &bp->b_lru)) {
			bp->b_state &= ~XFS_BSTATE_DISPOSE;
			atomic_inc(&bp->b_hold);
		}
		spin_unlock(&pag->pag_buf_lock);
	} else {
		/*
		 * most of the time buffers will already be removed from the
		 * LRU, so optimise that case by checking for the
		 * XFS_BSTATE_DISPOSE flag indicating the last list the buffer
		 * was on was the disposal list
		 */
		if (!(bp->b_state & XFS_BSTATE_DISPOSE)) {
			list_lru_del(&bp->b_target->bt_lru, &bp->b_lru);
		} else {
			ASSERT(list_empty(&bp->b_lru));
		}

		ASSERT(!(bp->b_flags & _XBF_DELWRI_Q));
		rhashtable_remove_fast(&pag->pag_buf_hash, &bp->b_rhash_head,
				       xfs_buf_hash_params);
		spin_unlock(&pag->pag_buf_lock);
		xfs_perag_put(pag);
		freebuf = true;
	}

out_unlock:
	spin_unlock(&bp->b_lock);

	if (freebuf)
		xfs_buf_free(bp);
}