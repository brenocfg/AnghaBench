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
typedef  int /*<<< orphan*/  u8 ;
struct slim_val_inf {int /*<<< orphan*/ * rbuf; } ;
struct slim_msg_txn {scalar_t__ comp; struct slim_val_inf* msg; } ;
struct slim_controller {int /*<<< orphan*/  dev; int /*<<< orphan*/  txn_lock; int /*<<< orphan*/  tid_idr; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct slim_msg_txn* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slim_free_txn_tid (struct slim_controller*,struct slim_msg_txn*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void slim_msg_response(struct slim_controller *ctrl, u8 *reply, u8 tid, u8 len)
{
	struct slim_msg_txn *txn;
	struct slim_val_inf *msg;
	unsigned long flags;

	spin_lock_irqsave(&ctrl->txn_lock, flags);
	txn = idr_find(&ctrl->tid_idr, tid);
	spin_unlock_irqrestore(&ctrl->txn_lock, flags);

	if (txn == NULL)
		return;

	msg = txn->msg;
	if (msg == NULL || msg->rbuf == NULL) {
		dev_err(ctrl->dev, "Got response to invalid TID:%d, len:%d\n",
				tid, len);
		return;
	}

	slim_free_txn_tid(ctrl, txn);
	memcpy(msg->rbuf, reply, len);
	if (txn->comp)
		complete(txn->comp);

	/* Remove runtime-pm vote now that response was received for TID txn */
	pm_runtime_mark_last_busy(ctrl->dev);
	pm_runtime_put_autosuspend(ctrl->dev);
}