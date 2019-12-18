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
typedef  int /*<<< orphan*/  uint64_t ;
struct xfs_trans {int /*<<< orphan*/  t_mountp; } ;
struct xfs_bmbt_irec {int /*<<< orphan*/  br_state; int /*<<< orphan*/  br_blockcount; int /*<<< orphan*/  br_startoff; int /*<<< orphan*/  br_startblock; } ;
struct xfs_rmap_intent {int ri_type; int ri_whichfork; int /*<<< orphan*/  ri_list; struct xfs_bmbt_irec ri_bmap; int /*<<< orphan*/  ri_owner; } ;
typedef  enum xfs_rmap_intent_type { ____Placeholder_xfs_rmap_intent_type } xfs_rmap_intent_type ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KM_NOFS ; 
 int /*<<< orphan*/  XFS_DEFER_OPS_TYPE_RMAP ; 
 int /*<<< orphan*/  XFS_FSB_TO_AGBNO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_FSB_TO_AGNO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xfs_rmap_intent* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_rmap_defer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_defer_add (struct xfs_trans*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
__xfs_rmap_add(
	struct xfs_trans		*tp,
	enum xfs_rmap_intent_type	type,
	uint64_t			owner,
	int				whichfork,
	struct xfs_bmbt_irec		*bmap)
{
	struct xfs_rmap_intent		*ri;

	trace_xfs_rmap_defer(tp->t_mountp,
			XFS_FSB_TO_AGNO(tp->t_mountp, bmap->br_startblock),
			type,
			XFS_FSB_TO_AGBNO(tp->t_mountp, bmap->br_startblock),
			owner, whichfork,
			bmap->br_startoff,
			bmap->br_blockcount,
			bmap->br_state);

	ri = kmem_alloc(sizeof(struct xfs_rmap_intent), KM_NOFS);
	INIT_LIST_HEAD(&ri->ri_list);
	ri->ri_type = type;
	ri->ri_owner = owner;
	ri->ri_whichfork = whichfork;
	ri->ri_bmap = *bmap;

	xfs_defer_add(tp, XFS_DEFER_OPS_TYPE_RMAP, &ri->ri_list);
}