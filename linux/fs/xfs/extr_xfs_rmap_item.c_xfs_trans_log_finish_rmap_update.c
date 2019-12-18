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
typedef  int /*<<< orphan*/  xfs_fileoff_t ;
typedef  int /*<<< orphan*/  xfs_filblks_t ;
typedef  int /*<<< orphan*/  xfs_exntst_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct xfs_trans {int /*<<< orphan*/  t_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  li_flags; } ;
struct xfs_rud_log_item {TYPE_1__ rud_item; } ;
struct xfs_btree_cur {int dummy; } ;
typedef  enum xfs_rmap_intent_type { ____Placeholder_xfs_rmap_intent_type } xfs_rmap_intent_type ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_LI_DIRTY ; 
 int /*<<< orphan*/  XFS_TRANS_DIRTY ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xfs_rmap_finish_one (struct xfs_trans*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xfs_btree_cur**) ; 

__attribute__((used)) static int
xfs_trans_log_finish_rmap_update(
	struct xfs_trans		*tp,
	struct xfs_rud_log_item		*rudp,
	enum xfs_rmap_intent_type	type,
	uint64_t			owner,
	int				whichfork,
	xfs_fileoff_t			startoff,
	xfs_fsblock_t			startblock,
	xfs_filblks_t			blockcount,
	xfs_exntst_t			state,
	struct xfs_btree_cur		**pcur)
{
	int				error;

	error = xfs_rmap_finish_one(tp, type, owner, whichfork, startoff,
			startblock, blockcount, state, pcur);

	/*
	 * Mark the transaction dirty, even on error. This ensures the
	 * transaction is aborted, which:
	 *
	 * 1.) releases the RUI and frees the RUD
	 * 2.) shuts down the filesystem
	 */
	tp->t_flags |= XFS_TRANS_DIRTY;
	set_bit(XFS_LI_DIRTY, &rudp->rud_item.li_flags);

	return error;
}