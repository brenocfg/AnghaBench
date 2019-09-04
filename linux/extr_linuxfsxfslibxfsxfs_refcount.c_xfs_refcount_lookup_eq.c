#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_agblock_t ;
struct TYPE_7__ {scalar_t__ rc_blockcount; int /*<<< orphan*/  rc_startblock; } ;
struct TYPE_8__ {TYPE_3__ rc; } ;
struct TYPE_5__ {int /*<<< orphan*/  agno; } ;
struct TYPE_6__ {TYPE_1__ a; } ;
struct xfs_btree_cur {TYPE_4__ bc_rec; TYPE_2__ bc_private; int /*<<< orphan*/  bc_mp; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_LOOKUP_EQ ; 
 int /*<<< orphan*/  XFS_LOOKUP_LE ; 
 int /*<<< orphan*/  trace_xfs_refcount_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xfs_btree_lookup (struct xfs_btree_cur*,int /*<<< orphan*/ ,int*) ; 

int
xfs_refcount_lookup_eq(
	struct xfs_btree_cur	*cur,
	xfs_agblock_t		bno,
	int			*stat)
{
	trace_xfs_refcount_lookup(cur->bc_mp, cur->bc_private.a.agno, bno,
			XFS_LOOKUP_LE);
	cur->bc_rec.rc.rc_startblock = bno;
	cur->bc_rec.rc.rc_blockcount = 0;
	return xfs_btree_lookup(cur, XFS_LOOKUP_EQ, stat);
}