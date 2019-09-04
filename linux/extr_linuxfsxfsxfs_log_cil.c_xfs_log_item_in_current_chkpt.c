#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xfs_log_item {int /*<<< orphan*/  li_seq; TYPE_3__* li_mountp; int /*<<< orphan*/  li_cil; } ;
struct xfs_cil_ctx {int /*<<< orphan*/  sequence; } ;
struct TYPE_6__ {TYPE_2__* m_log; } ;
struct TYPE_5__ {TYPE_1__* l_cilp; } ;
struct TYPE_4__ {struct xfs_cil_ctx* xc_ctx; } ;

/* Variables and functions */
 scalar_t__ XFS_LSN_CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

bool
xfs_log_item_in_current_chkpt(
	struct xfs_log_item *lip)
{
	struct xfs_cil_ctx *ctx;

	if (list_empty(&lip->li_cil))
		return false;

	ctx = lip->li_mountp->m_log->l_cilp->xc_ctx;

	/*
	 * li_seq is written on the first commit of a log item to record the
	 * first checkpoint it is written to. Hence if it is different to the
	 * current sequence, we're in a new checkpoint.
	 */
	if (XFS_LSN_CMP(lip->li_seq, ctx->sequence) != 0)
		return false;
	return true;
}