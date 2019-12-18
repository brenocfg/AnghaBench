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
typedef  int /*<<< orphan*/  xfs_fsblock_t ;
typedef  int /*<<< orphan*/  xfs_extlen_t ;
struct xfs_trans {int /*<<< orphan*/  t_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  li_flags; } ;
struct xfs_cud_log_item {TYPE_1__ cud_item; } ;
struct xfs_btree_cur {int dummy; } ;
typedef  enum xfs_refcount_intent_type { ____Placeholder_xfs_refcount_intent_type } xfs_refcount_intent_type ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_LI_DIRTY ; 
 int /*<<< orphan*/  XFS_TRANS_DIRTY ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xfs_refcount_finish_one (struct xfs_trans*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct xfs_btree_cur**) ; 

__attribute__((used)) static int
xfs_trans_log_finish_refcount_update(
	struct xfs_trans		*tp,
	struct xfs_cud_log_item		*cudp,
	enum xfs_refcount_intent_type	type,
	xfs_fsblock_t			startblock,
	xfs_extlen_t			blockcount,
	xfs_fsblock_t			*new_fsb,
	xfs_extlen_t			*new_len,
	struct xfs_btree_cur		**pcur)
{
	int				error;

	error = xfs_refcount_finish_one(tp, type, startblock,
			blockcount, new_fsb, new_len, pcur);

	/*
	 * Mark the transaction dirty, even on error. This ensures the
	 * transaction is aborted, which:
	 *
	 * 1.) releases the CUI and frees the CUD
	 * 2.) shuts down the filesystem
	 */
	tp->t_flags |= XFS_TRANS_DIRTY;
	set_bit(XFS_LI_DIRTY, &cudp->cud_item.li_flags);

	return error;
}