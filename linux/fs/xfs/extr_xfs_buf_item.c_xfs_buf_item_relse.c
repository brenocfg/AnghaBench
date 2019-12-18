#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * b_iodone; int /*<<< orphan*/  b_li_list; struct xfs_buf_log_item* b_log_item; } ;
typedef  TYPE_2__ xfs_buf_t ;
struct TYPE_6__ {int li_flags; } ;
struct xfs_buf_log_item {TYPE_1__ bli_item; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int XFS_LI_IN_AIL ; 
 int /*<<< orphan*/  _RET_IP_ ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_xfs_buf_item_relse (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_buf_item_free (struct xfs_buf_log_item*) ; 
 int /*<<< orphan*/  xfs_buf_rele (TYPE_2__*) ; 

void
xfs_buf_item_relse(
	xfs_buf_t	*bp)
{
	struct xfs_buf_log_item	*bip = bp->b_log_item;

	trace_xfs_buf_item_relse(bp, _RET_IP_);
	ASSERT(!(bip->bli_item.li_flags & XFS_LI_IN_AIL));

	bp->b_log_item = NULL;
	if (list_empty(&bp->b_li_list))
		bp->b_iodone = NULL;

	xfs_buf_rele(bp);
	xfs_buf_item_free(bip);
}