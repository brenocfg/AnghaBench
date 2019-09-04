#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct slim_val_inf {int num_bytes; scalar_t__* wbuf; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct slim_sched {scalar_t__ clk_state; int /*<<< orphan*/  m_reconf; int /*<<< orphan*/  pause_comp; } ;
struct slim_controller {int (* wakeup ) (struct slim_controller*) ;int /*<<< orphan*/  txn_lock; int /*<<< orphan*/  tid_idr; struct slim_sched sched; } ;
struct TYPE_4__ {int rl; int /*<<< orphan*/  mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_SLIM_BCAST_TXN (TYPE_1__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct slim_val_inf*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 scalar_t__ SLIM_CLK_ACTIVE ; 
 scalar_t__ SLIM_CLK_ENTERING_PAUSE ; 
 scalar_t__ SLIM_CLK_PAUSED ; 
 scalar_t__ SLIM_CLK_UNSPECIFIED ; 
 int /*<<< orphan*/  SLIM_LA_MANAGER ; 
 int SLIM_MAX_TIDS ; 
 int /*<<< orphan*/  SLIM_MSG_MC_BEGIN_RECONFIGURATION ; 
 int /*<<< orphan*/  SLIM_MSG_MC_NEXT_PAUSE_CLOCK ; 
 int /*<<< orphan*/  SLIM_MSG_MC_RECONFIGURE_NOW ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 scalar_t__ idr_find (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int slim_do_transfer (struct slim_controller*,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int stub1 (struct slim_controller*) ; 
 TYPE_1__ txn ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int slim_ctrl_clk_pause(struct slim_controller *ctrl, bool wakeup, u8 restart)
{
	int i, ret = 0;
	unsigned long flags;
	struct slim_sched *sched = &ctrl->sched;
	struct slim_val_inf msg = {0, 0, NULL, NULL};

	DEFINE_SLIM_BCAST_TXN(txn, SLIM_MSG_MC_BEGIN_RECONFIGURATION,
				3, SLIM_LA_MANAGER, &msg);

	if (wakeup == false && restart > SLIM_CLK_UNSPECIFIED)
		return -EINVAL;

	mutex_lock(&sched->m_reconf);
	if (wakeup) {
		if (sched->clk_state == SLIM_CLK_ACTIVE) {
			mutex_unlock(&sched->m_reconf);
			return 0;
		}

		/*
		 * Fine-tune calculation based on clock gear,
		 * message-bandwidth after bandwidth management
		 */
		ret = wait_for_completion_timeout(&sched->pause_comp,
				msecs_to_jiffies(100));
		if (!ret) {
			mutex_unlock(&sched->m_reconf);
			pr_err("Previous clock pause did not finish");
			return -ETIMEDOUT;
		}
		ret = 0;

		/*
		 * Slimbus framework will call controller wakeup
		 * Controller should make sure that it sets active framer
		 * out of clock pause
		 */
		if (sched->clk_state == SLIM_CLK_PAUSED && ctrl->wakeup)
			ret = ctrl->wakeup(ctrl);
		if (!ret)
			sched->clk_state = SLIM_CLK_ACTIVE;
		mutex_unlock(&sched->m_reconf);

		return ret;
	}

	/* already paused */
	if (ctrl->sched.clk_state == SLIM_CLK_PAUSED) {
		mutex_unlock(&sched->m_reconf);
		return 0;
	}

	spin_lock_irqsave(&ctrl->txn_lock, flags);
	for (i = 0; i < SLIM_MAX_TIDS; i++) {
		/* Pending response for a message */
		if (idr_find(&ctrl->tid_idr, i)) {
			spin_unlock_irqrestore(&ctrl->txn_lock, flags);
			mutex_unlock(&sched->m_reconf);
			return -EBUSY;
		}
	}
	spin_unlock_irqrestore(&ctrl->txn_lock, flags);

	sched->clk_state = SLIM_CLK_ENTERING_PAUSE;

	/* clock pause sequence */
	ret = slim_do_transfer(ctrl, &txn);
	if (ret)
		goto clk_pause_ret;

	txn.mc = SLIM_MSG_MC_NEXT_PAUSE_CLOCK;
	txn.rl = 4;
	msg.num_bytes = 1;
	msg.wbuf = &restart;
	ret = slim_do_transfer(ctrl, &txn);
	if (ret)
		goto clk_pause_ret;

	txn.mc = SLIM_MSG_MC_RECONFIGURE_NOW;
	txn.rl = 3;
	msg.num_bytes = 1;
	msg.wbuf = NULL;
	ret = slim_do_transfer(ctrl, &txn);

clk_pause_ret:
	if (ret) {
		sched->clk_state = SLIM_CLK_ACTIVE;
	} else {
		sched->clk_state = SLIM_CLK_PAUSED;
		complete(&sched->pause_comp);
	}
	mutex_unlock(&sched->m_reconf);

	return ret;
}