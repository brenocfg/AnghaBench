#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xfs_trans_t ;
struct TYPE_6__ {int /*<<< orphan*/ * b_transp; struct xfs_buf_log_item* b_log_item; } ;
typedef  TYPE_2__ xfs_buf_t ;
struct TYPE_5__ {int /*<<< orphan*/  li_cb; } ;
struct xfs_buf_log_item {TYPE_1__ bli_item; int /*<<< orphan*/  bli_flags; int /*<<< orphan*/  bli_refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  XFS_BLFT_DINO_BUF ; 
 int /*<<< orphan*/  XFS_BLI_STALE_INODE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfs_buf_iodone ; 
 int /*<<< orphan*/  xfs_trans_buf_set_type (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

void
xfs_trans_stale_inode_buf(
	xfs_trans_t		*tp,
	xfs_buf_t		*bp)
{
	struct xfs_buf_log_item	*bip = bp->b_log_item;

	ASSERT(bp->b_transp == tp);
	ASSERT(bip != NULL);
	ASSERT(atomic_read(&bip->bli_refcount) > 0);

	bip->bli_flags |= XFS_BLI_STALE_INODE;
	bip->bli_item.li_cb = xfs_buf_iodone;
	xfs_trans_buf_set_type(tp, bp, XFS_BLFT_DINO_BUF);
}