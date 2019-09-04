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
struct fc_rport {scalar_t__ dd_data; } ;
struct csio_rnode {int /*<<< orphan*/  nport_id; } ;
struct csio_lnode {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  evtq_work; } ;
struct csio_hw {int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  evtq_work; } ;
typedef  int /*<<< orphan*/  rn ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_EVT_DEV_LOSS ; 
 int CSIO_HWF_FWEVT_PENDING ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_lnode*,int /*<<< orphan*/ ) ; 
 scalar_t__ csio_enqueue_evt (struct csio_lnode*,int /*<<< orphan*/ ,struct csio_rnode**,int) ; 
 scalar_t__ csio_is_hw_removing (struct csio_lnode*) ; 
 scalar_t__ csio_is_rnode_ready (struct csio_rnode*) ; 
 int /*<<< orphan*/  csio_ln_dbg (struct csio_lnode*,char*,struct csio_rnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct csio_lnode* csio_lnode_to_hw (struct csio_lnode*) ; 
 int /*<<< orphan*/  csio_rn_flowid (struct csio_rnode*) ; 
 struct csio_lnode* csio_rnode_to_lnode (struct csio_rnode*) ; 
 int /*<<< orphan*/  n_dev_loss_tmo ; 
 int /*<<< orphan*/  n_evt_drop ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
csio_dev_loss_tmo_callbk(struct fc_rport *rport)
{
	struct csio_rnode *rn;
	struct csio_hw *hw;
	struct csio_lnode *ln;

	rn = *((struct csio_rnode **)rport->dd_data);
	ln = csio_rnode_to_lnode(rn);
	hw = csio_lnode_to_hw(ln);

	spin_lock_irq(&hw->lock);

	/* return if driver is being removed or same rnode comes back online */
	if (csio_is_hw_removing(hw) || csio_is_rnode_ready(rn))
		goto out;

	csio_ln_dbg(ln, "devloss timeout on rnode:%p portid:x%x flowid:x%x\n",
		    rn, rn->nport_id, csio_rn_flowid(rn));

	CSIO_INC_STATS(ln, n_dev_loss_tmo);

	/*
	 * enqueue devloss event to event worker thread to serialize all
	 * rnode events.
	 */
	if (csio_enqueue_evt(hw, CSIO_EVT_DEV_LOSS, &rn, sizeof(rn))) {
		CSIO_INC_STATS(hw, n_evt_drop);
		goto out;
	}

	if (!(hw->flags & CSIO_HWF_FWEVT_PENDING)) {
		hw->flags |= CSIO_HWF_FWEVT_PENDING;
		spin_unlock_irq(&hw->lock);
		schedule_work(&hw->evtq_work);
		return;
	}

out:
	spin_unlock_irq(&hw->lock);
}