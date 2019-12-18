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
typedef  int /*<<< orphan*/  xfs_agnumber_t ;
typedef  int xfs_agblock_t ;
typedef  union xfs_btree_rec {int dummy; } xfs_btree_rec ;
struct xfs_refcount_irec {int rc_blockcount; int rc_startblock; int rc_refcount; } ;
struct xfs_mount {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  agno; } ;
struct TYPE_4__ {TYPE_1__ a; } ;
struct xfs_btree_cur {TYPE_2__ bc_private; struct xfs_mount* bc_mp; } ;

/* Variables and functions */
 int EFSCORRUPTED ; 
 int MAXREFCEXTLEN ; 
 int MAXREFCOUNT ; 
 int XFS_REFC_COW_START ; 
 int /*<<< orphan*/  trace_xfs_refcount_get (struct xfs_mount*,int /*<<< orphan*/ ,struct xfs_refcount_irec*) ; 
 int xfs_btree_get_rec (struct xfs_btree_cur*,union xfs_btree_rec**,int*) ; 
 int /*<<< orphan*/  xfs_refcount_btrec_to_irec (union xfs_btree_rec*,struct xfs_refcount_irec*) ; 
 int /*<<< orphan*/  xfs_verify_agbno (struct xfs_mount*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_warn (struct xfs_mount*,char*,int,...) ; 

int
xfs_refcount_get_rec(
	struct xfs_btree_cur		*cur,
	struct xfs_refcount_irec	*irec,
	int				*stat)
{
	struct xfs_mount		*mp = cur->bc_mp;
	xfs_agnumber_t			agno = cur->bc_private.a.agno;
	union xfs_btree_rec		*rec;
	int				error;
	xfs_agblock_t			realstart;

	error = xfs_btree_get_rec(cur, &rec, stat);
	if (error || !*stat)
		return error;

	xfs_refcount_btrec_to_irec(rec, irec);

	agno = cur->bc_private.a.agno;
	if (irec->rc_blockcount == 0 || irec->rc_blockcount > MAXREFCEXTLEN)
		goto out_bad_rec;

	/* handle special COW-staging state */
	realstart = irec->rc_startblock;
	if (realstart & XFS_REFC_COW_START) {
		if (irec->rc_refcount != 1)
			goto out_bad_rec;
		realstart &= ~XFS_REFC_COW_START;
	} else if (irec->rc_refcount < 2) {
		goto out_bad_rec;
	}

	/* check for valid extent range, including overflow */
	if (!xfs_verify_agbno(mp, agno, realstart))
		goto out_bad_rec;
	if (realstart > realstart + irec->rc_blockcount)
		goto out_bad_rec;
	if (!xfs_verify_agbno(mp, agno, realstart + irec->rc_blockcount - 1))
		goto out_bad_rec;

	if (irec->rc_refcount == 0 || irec->rc_refcount > MAXREFCOUNT)
		goto out_bad_rec;

	trace_xfs_refcount_get(cur->bc_mp, cur->bc_private.a.agno, irec);
	return 0;

out_bad_rec:
	xfs_warn(mp,
		"Refcount BTree record corruption in AG %d detected!", agno);
	xfs_warn(mp,
		"Start block 0x%x, block count 0x%x, references 0x%x",
		irec->rc_startblock, irec->rc_blockcount, irec->rc_refcount);
	return -EFSCORRUPTED;
}