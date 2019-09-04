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
struct slim_msg_txn {int tid; } ;
struct slim_controller {int /*<<< orphan*/  txn_lock; int /*<<< orphan*/  tid_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  SLIM_MAX_TIDS ; 
 int idr_alloc_cyclic (int /*<<< orphan*/ *,struct slim_msg_txn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int slim_alloc_txn_tid(struct slim_controller *ctrl, struct slim_msg_txn *txn)
{
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&ctrl->txn_lock, flags);
	ret = idr_alloc_cyclic(&ctrl->tid_idr, txn, 0,
				SLIM_MAX_TIDS, GFP_ATOMIC);
	if (ret < 0) {
		spin_unlock_irqrestore(&ctrl->txn_lock, flags);
		return ret;
	}
	txn->tid = ret;
	spin_unlock_irqrestore(&ctrl->txn_lock, flags);
	return 0;
}