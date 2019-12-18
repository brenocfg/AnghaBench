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
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
typedef  int /*<<< orphan*/  xfs_extlen_t ;
struct xfs_trans {int /*<<< orphan*/  t_mountp; } ;
struct xfs_refcount_intent {int ri_type; int /*<<< orphan*/  ri_list; int /*<<< orphan*/  ri_blockcount; int /*<<< orphan*/  ri_startblock; } ;
typedef  enum xfs_refcount_intent_type { ____Placeholder_xfs_refcount_intent_type } xfs_refcount_intent_type ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KM_NOFS ; 
 int /*<<< orphan*/  XFS_DEFER_OPS_TYPE_REFCOUNT ; 
 int /*<<< orphan*/  XFS_FSB_TO_AGBNO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_FSB_TO_AGNO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xfs_refcount_intent* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_refcount_defer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_defer_add (struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__xfs_refcount_add(
	struct xfs_trans		*tp,
	enum xfs_refcount_intent_type	type,
	xfs_fsblock_t			startblock,
	xfs_extlen_t			blockcount)
{
	struct xfs_refcount_intent	*ri;

	trace_xfs_refcount_defer(tp->t_mountp,
			XFS_FSB_TO_AGNO(tp->t_mountp, startblock),
			type, XFS_FSB_TO_AGBNO(tp->t_mountp, startblock),
			blockcount);

	ri = kmem_alloc(sizeof(struct xfs_refcount_intent),
			KM_NOFS);
	INIT_LIST_HEAD(&ri->ri_list);
	ri->ri_type = type;
	ri->ri_startblock = startblock;
	ri->ri_blockcount = blockcount;

	xfs_defer_add(tp, XFS_DEFER_OPS_TYPE_REFCOUNT, &ri->ri_list);
}