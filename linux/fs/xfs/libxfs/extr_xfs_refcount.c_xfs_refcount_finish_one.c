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
typedef  scalar_t__ xfs_fsblock_t ;
typedef  scalar_t__ xfs_extlen_t ;
typedef  scalar_t__ xfs_agnumber_t ;
typedef  int /*<<< orphan*/  xfs_agblock_t ;
struct xfs_trans {struct xfs_mount* t_mountp; } ;
struct xfs_mount {int dummy; } ;
struct xfs_buf {int dummy; } ;
struct TYPE_5__ {unsigned long nr_ops; int shape_changes; } ;
struct TYPE_6__ {TYPE_1__ refc; } ;
struct TYPE_7__ {scalar_t__ agno; TYPE_2__ priv; } ;
struct TYPE_8__ {TYPE_3__ a; } ;
struct xfs_btree_cur {TYPE_4__ bc_private; } ;
typedef  enum xfs_refcount_intent_type { ____Placeholder_xfs_refcount_intent_type } xfs_refcount_intent_type ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int EFSCORRUPTED ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ NULLAGNUMBER ; 
 scalar_t__ XFS_AGB_TO_FSB (struct xfs_mount*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_ALLOC_FLAG_FREEING ; 
 int /*<<< orphan*/  XFS_ERRTAG_REFCOUNT_FINISH_ONE ; 
 int /*<<< orphan*/  XFS_FSB_TO_AGBNO (struct xfs_mount*,scalar_t__) ; 
 scalar_t__ XFS_FSB_TO_AGNO (struct xfs_mount*,scalar_t__) ; 
 int /*<<< orphan*/  XFS_REFCOUNT_ADJUST_DECREASE ; 
 int /*<<< orphan*/  XFS_REFCOUNT_ADJUST_INCREASE ; 
#define  XFS_REFCOUNT_ALLOC_COW 131 
#define  XFS_REFCOUNT_DECREASE 130 
#define  XFS_REFCOUNT_FREE_COW 129 
#define  XFS_REFCOUNT_INCREASE 128 
 scalar_t__ XFS_TEST_ERROR (int,struct xfs_mount*,int /*<<< orphan*/ ) ; 
 int __xfs_refcount_cow_alloc (struct xfs_btree_cur*,int /*<<< orphan*/ ,scalar_t__) ; 
 int __xfs_refcount_cow_free (struct xfs_btree_cur*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_refcount_deferred (struct xfs_mount*,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  trace_xfs_refcount_finish_one_leftover (struct xfs_mount*,scalar_t__,int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int xfs_alloc_read_agf (struct xfs_mount*,struct xfs_trans*,scalar_t__,int /*<<< orphan*/ ,struct xfs_buf**) ; 
 int xfs_refcount_adjust (struct xfs_btree_cur*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_refcount_finish_one_cleanup (struct xfs_trans*,struct xfs_btree_cur*,int /*<<< orphan*/ ) ; 
 struct xfs_btree_cur* xfs_refcountbt_init_cursor (struct xfs_mount*,struct xfs_trans*,struct xfs_buf*,scalar_t__) ; 
 int /*<<< orphan*/  xfs_trans_brelse (struct xfs_trans*,struct xfs_buf*) ; 

int
xfs_refcount_finish_one(
	struct xfs_trans		*tp,
	enum xfs_refcount_intent_type	type,
	xfs_fsblock_t			startblock,
	xfs_extlen_t			blockcount,
	xfs_fsblock_t			*new_fsb,
	xfs_extlen_t			*new_len,
	struct xfs_btree_cur		**pcur)
{
	struct xfs_mount		*mp = tp->t_mountp;
	struct xfs_btree_cur		*rcur;
	struct xfs_buf			*agbp = NULL;
	int				error = 0;
	xfs_agnumber_t			agno;
	xfs_agblock_t			bno;
	xfs_agblock_t			new_agbno;
	unsigned long			nr_ops = 0;
	int				shape_changes = 0;

	agno = XFS_FSB_TO_AGNO(mp, startblock);
	ASSERT(agno != NULLAGNUMBER);
	bno = XFS_FSB_TO_AGBNO(mp, startblock);

	trace_xfs_refcount_deferred(mp, XFS_FSB_TO_AGNO(mp, startblock),
			type, XFS_FSB_TO_AGBNO(mp, startblock),
			blockcount);

	if (XFS_TEST_ERROR(false, mp,
			XFS_ERRTAG_REFCOUNT_FINISH_ONE))
		return -EIO;

	/*
	 * If we haven't gotten a cursor or the cursor AG doesn't match
	 * the startblock, get one now.
	 */
	rcur = *pcur;
	if (rcur != NULL && rcur->bc_private.a.agno != agno) {
		nr_ops = rcur->bc_private.a.priv.refc.nr_ops;
		shape_changes = rcur->bc_private.a.priv.refc.shape_changes;
		xfs_refcount_finish_one_cleanup(tp, rcur, 0);
		rcur = NULL;
		*pcur = NULL;
	}
	if (rcur == NULL) {
		error = xfs_alloc_read_agf(tp->t_mountp, tp, agno,
				XFS_ALLOC_FLAG_FREEING, &agbp);
		if (error)
			return error;
		if (!agbp)
			return -EFSCORRUPTED;

		rcur = xfs_refcountbt_init_cursor(mp, tp, agbp, agno);
		if (!rcur) {
			error = -ENOMEM;
			goto out_cur;
		}
		rcur->bc_private.a.priv.refc.nr_ops = nr_ops;
		rcur->bc_private.a.priv.refc.shape_changes = shape_changes;
	}
	*pcur = rcur;

	switch (type) {
	case XFS_REFCOUNT_INCREASE:
		error = xfs_refcount_adjust(rcur, bno, blockcount, &new_agbno,
			new_len, XFS_REFCOUNT_ADJUST_INCREASE, NULL);
		*new_fsb = XFS_AGB_TO_FSB(mp, agno, new_agbno);
		break;
	case XFS_REFCOUNT_DECREASE:
		error = xfs_refcount_adjust(rcur, bno, blockcount, &new_agbno,
			new_len, XFS_REFCOUNT_ADJUST_DECREASE, NULL);
		*new_fsb = XFS_AGB_TO_FSB(mp, agno, new_agbno);
		break;
	case XFS_REFCOUNT_ALLOC_COW:
		*new_fsb = startblock + blockcount;
		*new_len = 0;
		error = __xfs_refcount_cow_alloc(rcur, bno, blockcount);
		break;
	case XFS_REFCOUNT_FREE_COW:
		*new_fsb = startblock + blockcount;
		*new_len = 0;
		error = __xfs_refcount_cow_free(rcur, bno, blockcount);
		break;
	default:
		ASSERT(0);
		error = -EFSCORRUPTED;
	}
	if (!error && *new_len > 0)
		trace_xfs_refcount_finish_one_leftover(mp, agno, type,
				bno, blockcount, new_agbno, *new_len);
	return error;

out_cur:
	xfs_trans_brelse(tp, agbp);

	return error;
}