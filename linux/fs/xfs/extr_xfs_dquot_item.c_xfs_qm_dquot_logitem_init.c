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
struct xfs_dq_logitem {struct xfs_dquot* qli_dquot; int /*<<< orphan*/  qli_item; } ;
struct xfs_dquot {int /*<<< orphan*/  q_mount; struct xfs_dq_logitem q_logitem; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFS_LI_DQUOT ; 
 int /*<<< orphan*/  xfs_dquot_item_ops ; 
 int /*<<< orphan*/  xfs_log_item_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
xfs_qm_dquot_logitem_init(
	struct xfs_dquot	*dqp)
{
	struct xfs_dq_logitem	*lp = &dqp->q_logitem;

	xfs_log_item_init(dqp->q_mount, &lp->qli_item, XFS_LI_DQUOT,
					&xfs_dquot_item_ops);
	lp->qli_dquot = dqp;
}