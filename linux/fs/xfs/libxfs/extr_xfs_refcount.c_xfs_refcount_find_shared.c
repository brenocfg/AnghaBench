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
typedef  scalar_t__ xfs_extlen_t ;
typedef  scalar_t__ xfs_agblock_t ;
struct xfs_refcount_irec {scalar_t__ rc_startblock; scalar_t__ rc_blockcount; } ;
struct TYPE_3__ {int /*<<< orphan*/  agno; } ;
struct TYPE_4__ {TYPE_1__ a; } ;
struct xfs_btree_cur {TYPE_2__ bc_private; int /*<<< orphan*/  bc_mp; } ;

/* Variables and functions */
 scalar_t__ NULLAGBLOCK ; 
 int /*<<< orphan*/  XFS_WANT_CORRUPTED_GOTO (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  out_error ; 
 int /*<<< orphan*/  trace_xfs_refcount_find_shared (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_refcount_find_shared_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_xfs_refcount_find_shared_result (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int xfs_btree_increment (struct xfs_btree_cur*,int /*<<< orphan*/ ,int*) ; 
 int xfs_refcount_get_rec (struct xfs_btree_cur*,struct xfs_refcount_irec*,int*) ; 
 int xfs_refcount_lookup_le (struct xfs_btree_cur*,scalar_t__,int*) ; 

int
xfs_refcount_find_shared(
	struct xfs_btree_cur		*cur,
	xfs_agblock_t			agbno,
	xfs_extlen_t			aglen,
	xfs_agblock_t			*fbno,
	xfs_extlen_t			*flen,
	bool				find_end_of_shared)
{
	struct xfs_refcount_irec	tmp;
	int				i;
	int				have;
	int				error;

	trace_xfs_refcount_find_shared(cur->bc_mp, cur->bc_private.a.agno,
			agbno, aglen);

	/* By default, skip the whole range */
	*fbno = NULLAGBLOCK;
	*flen = 0;

	/* Try to find a refcount extent that crosses the start */
	error = xfs_refcount_lookup_le(cur, agbno, &have);
	if (error)
		goto out_error;
	if (!have) {
		/* No left extent, look at the next one */
		error = xfs_btree_increment(cur, 0, &have);
		if (error)
			goto out_error;
		if (!have)
			goto done;
	}
	error = xfs_refcount_get_rec(cur, &tmp, &i);
	if (error)
		goto out_error;
	XFS_WANT_CORRUPTED_GOTO(cur->bc_mp, i == 1, out_error);

	/* If the extent ends before the start, look at the next one */
	if (tmp.rc_startblock + tmp.rc_blockcount <= agbno) {
		error = xfs_btree_increment(cur, 0, &have);
		if (error)
			goto out_error;
		if (!have)
			goto done;
		error = xfs_refcount_get_rec(cur, &tmp, &i);
		if (error)
			goto out_error;
		XFS_WANT_CORRUPTED_GOTO(cur->bc_mp, i == 1, out_error);
	}

	/* If the extent starts after the range we want, bail out */
	if (tmp.rc_startblock >= agbno + aglen)
		goto done;

	/* We found the start of a shared extent! */
	if (tmp.rc_startblock < agbno) {
		tmp.rc_blockcount -= (agbno - tmp.rc_startblock);
		tmp.rc_startblock = agbno;
	}

	*fbno = tmp.rc_startblock;
	*flen = min(tmp.rc_blockcount, agbno + aglen - *fbno);
	if (!find_end_of_shared)
		goto done;

	/* Otherwise, find the end of this shared extent */
	while (*fbno + *flen < agbno + aglen) {
		error = xfs_btree_increment(cur, 0, &have);
		if (error)
			goto out_error;
		if (!have)
			break;
		error = xfs_refcount_get_rec(cur, &tmp, &i);
		if (error)
			goto out_error;
		XFS_WANT_CORRUPTED_GOTO(cur->bc_mp, i == 1, out_error);
		if (tmp.rc_startblock >= agbno + aglen ||
		    tmp.rc_startblock != *fbno + *flen)
			break;
		*flen = min(*flen + tmp.rc_blockcount, agbno + aglen - *fbno);
	}

done:
	trace_xfs_refcount_find_shared_result(cur->bc_mp,
			cur->bc_private.a.agno, *fbno, *flen);

out_error:
	if (error)
		trace_xfs_refcount_find_shared_error(cur->bc_mp,
				cur->bc_private.a.agno, error, _RET_IP_);
	return error;
}