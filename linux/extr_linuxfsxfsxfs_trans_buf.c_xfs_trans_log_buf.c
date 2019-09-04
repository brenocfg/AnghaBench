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
typedef  int /*<<< orphan*/  uint ;
struct xfs_trans {int dummy; } ;
struct xfs_buf_log_item {int bli_flags; } ;
struct xfs_buf {int /*<<< orphan*/  b_length; struct xfs_buf_log_item* b_log_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  BBTOB (int /*<<< orphan*/ ) ; 
 int XFS_BLI_ORDERED ; 
 int /*<<< orphan*/  trace_xfs_trans_log_buf (struct xfs_buf_log_item*) ; 
 int /*<<< orphan*/  xfs_buf_item_log (struct xfs_buf_log_item*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_trans_dirty_buf (struct xfs_trans*,struct xfs_buf*) ; 

void
xfs_trans_log_buf(
	struct xfs_trans	*tp,
	struct xfs_buf		*bp,
	uint			first,
	uint			last)
{
	struct xfs_buf_log_item	*bip = bp->b_log_item;

	ASSERT(first <= last && last < BBTOB(bp->b_length));
	ASSERT(!(bip->bli_flags & XFS_BLI_ORDERED));

	xfs_trans_dirty_buf(tp, bp);

	trace_xfs_trans_log_buf(bip);
	xfs_buf_item_log(bip, first, last);
}