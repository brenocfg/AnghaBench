#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_5__ {struct xfs_buf_log_item* b_log_item; int /*<<< orphan*/ * b_transp; } ;
typedef  TYPE_1__ xfs_buf_t ;
struct xfs_mount {TYPE_1__* m_sb_bp; } ;
struct xfs_buf_log_item {int /*<<< orphan*/  bli_recur; int /*<<< orphan*/  bli_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  _xfs_trans_bjoin (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_trans_getsb (struct xfs_buf_log_item*) ; 
 int /*<<< orphan*/  trace_xfs_trans_getsb_recur (struct xfs_buf_log_item*) ; 
 TYPE_1__* xfs_getsb (struct xfs_mount*) ; 

xfs_buf_t *
xfs_trans_getsb(
	xfs_trans_t		*tp,
	struct xfs_mount	*mp)
{
	xfs_buf_t		*bp;
	struct xfs_buf_log_item	*bip;

	/*
	 * Default to just trying to lock the superblock buffer
	 * if tp is NULL.
	 */
	if (tp == NULL)
		return xfs_getsb(mp);

	/*
	 * If the superblock buffer already has this transaction
	 * pointer in its b_fsprivate2 field, then we know we already
	 * have it locked.  In this case we just increment the lock
	 * recursion count and return the buffer to the caller.
	 */
	bp = mp->m_sb_bp;
	if (bp->b_transp == tp) {
		bip = bp->b_log_item;
		ASSERT(bip != NULL);
		ASSERT(atomic_read(&bip->bli_refcount) > 0);
		bip->bli_recur++;
		trace_xfs_trans_getsb_recur(bip);
		return bp;
	}

	bp = xfs_getsb(mp);
	if (bp == NULL)
		return NULL;

	_xfs_trans_bjoin(tp, bp, 1);
	trace_xfs_trans_getsb(bp->b_log_item);
	return bp;
}