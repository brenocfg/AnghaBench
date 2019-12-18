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
typedef  int uint ;
struct xfs_trans_res {scalar_t__ tr_logres; } ;
struct xfs_trans {int t_flags; int /*<<< orphan*/  t_firstblock; int /*<<< orphan*/  t_dfops; int /*<<< orphan*/  t_busy; int /*<<< orphan*/  t_items; struct xfs_mount* t_mountp; int /*<<< orphan*/  t_magic; } ;
struct xfs_mount {int /*<<< orphan*/  m_active_trans; TYPE_2__* m_super; } ;
struct TYPE_3__ {scalar_t__ frozen; } ;
struct TYPE_4__ {TYPE_1__ s_writers; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NULLFSBLOCK ; 
 scalar_t__ SB_FREEZE_COMPLETE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  XFS_TRANS_HEADER_MAGIC ; 
 int XFS_TRANS_NO_WRITECOUNT ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct xfs_trans* kmem_zone_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_start_intwrite (TYPE_2__*) ; 
 int /*<<< orphan*/  trace_xfs_trans_alloc (struct xfs_trans*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_cancel (struct xfs_trans*) ; 
 int xfs_trans_reserve (struct xfs_trans*,struct xfs_trans_res*,int,int) ; 
 int /*<<< orphan*/  xfs_trans_zone ; 

int
xfs_trans_alloc(
	struct xfs_mount	*mp,
	struct xfs_trans_res	*resp,
	uint			blocks,
	uint			rtextents,
	uint			flags,
	struct xfs_trans	**tpp)
{
	struct xfs_trans	*tp;
	int			error;

	/*
	 * Allocate the handle before we do our freeze accounting and setting up
	 * GFP_NOFS allocation context so that we avoid lockdep false positives
	 * by doing GFP_KERNEL allocations inside sb_start_intwrite().
	 */
	tp = kmem_zone_zalloc(xfs_trans_zone, 0);
	if (!(flags & XFS_TRANS_NO_WRITECOUNT))
		sb_start_intwrite(mp->m_super);

	/*
	 * Zero-reservation ("empty") transactions can't modify anything, so
	 * they're allowed to run while we're frozen.
	 */
	WARN_ON(resp->tr_logres > 0 &&
		mp->m_super->s_writers.frozen == SB_FREEZE_COMPLETE);
	atomic_inc(&mp->m_active_trans);

	tp->t_magic = XFS_TRANS_HEADER_MAGIC;
	tp->t_flags = flags;
	tp->t_mountp = mp;
	INIT_LIST_HEAD(&tp->t_items);
	INIT_LIST_HEAD(&tp->t_busy);
	INIT_LIST_HEAD(&tp->t_dfops);
	tp->t_firstblock = NULLFSBLOCK;

	error = xfs_trans_reserve(tp, resp, blocks, rtextents);
	if (error) {
		xfs_trans_cancel(tp);
		return error;
	}

	trace_xfs_trans_alloc(tp, _RET_IP_);

	*tpp = tp;
	return 0;
}