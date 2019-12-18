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
typedef  int xfs_buf_flags_t ;
struct xfs_buftarg {int /*<<< orphan*/  bt_mount; } ;
struct xfs_buf_map {scalar_t__ bm_len; int /*<<< orphan*/  bm_bn; } ;
struct xfs_buf {int b_flags; int /*<<< orphan*/  b_mount; int /*<<< orphan*/  b_waiters; int /*<<< orphan*/  b_pin_count; scalar_t__ b_length; TYPE_1__* b_maps; int /*<<< orphan*/  b_bn; struct xfs_buftarg* b_target; int /*<<< orphan*/  b_lock; int /*<<< orphan*/  b_sema; int /*<<< orphan*/  b_li_list; int /*<<< orphan*/  b_list; int /*<<< orphan*/  b_lru; int /*<<< orphan*/  b_iowait; int /*<<< orphan*/  b_lru_ref; int /*<<< orphan*/  b_hold; } ;
struct TYPE_2__ {scalar_t__ bm_len; int /*<<< orphan*/  bm_bn; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KM_NOFS ; 
 int XBF_ASYNC ; 
 int XBF_READ_AHEAD ; 
 int XBF_TRYLOCK ; 
 int XBF_UNMAPPED ; 
 int /*<<< orphan*/  XFS_STATS_INC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_zone_free (int /*<<< orphan*/ ,struct xfs_buf*) ; 
 struct xfs_buf* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_buf_init (struct xfs_buf*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xb_create ; 
 int xfs_buf_get_maps (struct xfs_buf*,int) ; 
 int /*<<< orphan*/  xfs_buf_zone ; 

__attribute__((used)) static struct xfs_buf *
_xfs_buf_alloc(
	struct xfs_buftarg	*target,
	struct xfs_buf_map	*map,
	int			nmaps,
	xfs_buf_flags_t		flags)
{
	struct xfs_buf		*bp;
	int			error;
	int			i;

	bp = kmem_zone_zalloc(xfs_buf_zone, KM_NOFS);
	if (unlikely(!bp))
		return NULL;

	/*
	 * We don't want certain flags to appear in b_flags unless they are
	 * specifically set by later operations on the buffer.
	 */
	flags &= ~(XBF_UNMAPPED | XBF_TRYLOCK | XBF_ASYNC | XBF_READ_AHEAD);

	atomic_set(&bp->b_hold, 1);
	atomic_set(&bp->b_lru_ref, 1);
	init_completion(&bp->b_iowait);
	INIT_LIST_HEAD(&bp->b_lru);
	INIT_LIST_HEAD(&bp->b_list);
	INIT_LIST_HEAD(&bp->b_li_list);
	sema_init(&bp->b_sema, 0); /* held, no waiters */
	spin_lock_init(&bp->b_lock);
	bp->b_target = target;
	bp->b_mount = target->bt_mount;
	bp->b_flags = flags;

	/*
	 * Set length and io_length to the same value initially.
	 * I/O routines should use io_length, which will be the same in
	 * most cases but may be reset (e.g. XFS recovery).
	 */
	error = xfs_buf_get_maps(bp, nmaps);
	if (error)  {
		kmem_zone_free(xfs_buf_zone, bp);
		return NULL;
	}

	bp->b_bn = map[0].bm_bn;
	bp->b_length = 0;
	for (i = 0; i < nmaps; i++) {
		bp->b_maps[i].bm_bn = map[i].bm_bn;
		bp->b_maps[i].bm_len = map[i].bm_len;
		bp->b_length += map[i].bm_len;
	}

	atomic_set(&bp->b_pin_count, 0);
	init_waitqueue_head(&bp->b_waiters);

	XFS_STATS_INC(bp->b_mount, xb_create);
	trace_xfs_buf_init(bp, _RET_IP_);

	return bp;
}