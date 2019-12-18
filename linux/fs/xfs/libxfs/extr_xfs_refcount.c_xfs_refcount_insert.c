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
struct xfs_refcount_irec {int /*<<< orphan*/  rc_refcount; int /*<<< orphan*/  rc_blockcount; int /*<<< orphan*/  rc_startblock; } ;
struct TYPE_7__ {int /*<<< orphan*/  agno; } ;
struct TYPE_8__ {TYPE_3__ a; } ;
struct TYPE_5__ {int /*<<< orphan*/  rc_refcount; int /*<<< orphan*/  rc_blockcount; int /*<<< orphan*/  rc_startblock; } ;
struct TYPE_6__ {TYPE_1__ rc; } ;
struct xfs_btree_cur {TYPE_4__ bc_private; int /*<<< orphan*/  bc_mp; TYPE_2__ bc_rec; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_WANT_CORRUPTED_GOTO (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 int /*<<< orphan*/  out_error ; 
 int /*<<< orphan*/  trace_xfs_refcount_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_refcount_irec*) ; 
 int /*<<< orphan*/  trace_xfs_refcount_insert_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int xfs_btree_insert (struct xfs_btree_cur*,int*) ; 

int
xfs_refcount_insert(
	struct xfs_btree_cur		*cur,
	struct xfs_refcount_irec	*irec,
	int				*i)
{
	int				error;

	trace_xfs_refcount_insert(cur->bc_mp, cur->bc_private.a.agno, irec);
	cur->bc_rec.rc.rc_startblock = irec->rc_startblock;
	cur->bc_rec.rc.rc_blockcount = irec->rc_blockcount;
	cur->bc_rec.rc.rc_refcount = irec->rc_refcount;
	error = xfs_btree_insert(cur, i);
	if (error)
		goto out_error;
	XFS_WANT_CORRUPTED_GOTO(cur->bc_mp, *i == 1, out_error);

out_error:
	if (error)
		trace_xfs_refcount_insert_error(cur->bc_mp,
				cur->bc_private.a.agno, error, _RET_IP_);
	return error;
}