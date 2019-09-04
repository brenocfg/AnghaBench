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
struct csio_q {int dummy; } ;
struct csio_hw {scalar_t__ intr_mode; int flags; int /*<<< orphan*/  lock; int /*<<< orphan*/  evtq_work; int /*<<< orphan*/  intr_iq_idx; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSIO_DB_ASSERT (struct csio_q*) ; 
 int CSIO_HWF_FWEVT_PENDING ; 
 scalar_t__ CSIO_IM_INTX ; 
 int /*<<< orphan*/  CSIO_INC_STATS (struct csio_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MYPF_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCIE_PF_CLI_A ; 
 struct csio_q* csio_get_q (struct csio_hw*,int /*<<< orphan*/ ) ; 
 scalar_t__ csio_hw_slow_intr_handler (struct csio_hw*) ; 
 int csio_mb_isr_handler (struct csio_hw*) ; 
 scalar_t__ csio_wr_process_iq (struct csio_hw*,struct csio_q*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  csio_wr_reg32 (struct csio_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  n_pcich_offline ; 
 int pci_channel_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static irqreturn_t
csio_fcoe_isr(int irq, void *dev_id)
{
	struct csio_hw *hw = (struct csio_hw *) dev_id;
	struct csio_q *intx_q = NULL;
	int rv;
	irqreturn_t ret = IRQ_NONE;
	unsigned long flags;

	if (unlikely(!hw))
		return IRQ_NONE;

	if (unlikely(pci_channel_offline(hw->pdev))) {
		CSIO_INC_STATS(hw, n_pcich_offline);
		return IRQ_NONE;
	}

	/* Disable the interrupt for this PCI function. */
	if (hw->intr_mode == CSIO_IM_INTX)
		csio_wr_reg32(hw, 0, MYPF_REG(PCIE_PF_CLI_A));

	/*
	 * The read in the following function will flush the
	 * above write.
	 */
	if (csio_hw_slow_intr_handler(hw))
		ret = IRQ_HANDLED;

	/* Get the INTx Forward interrupt IQ. */
	intx_q = csio_get_q(hw, hw->intr_iq_idx);

	CSIO_DB_ASSERT(intx_q);

	/* IQ handler is not possible for intx_q, hence pass in NULL */
	if (likely(csio_wr_process_iq(hw, intx_q, NULL, NULL) == 0))
		ret = IRQ_HANDLED;

	spin_lock_irqsave(&hw->lock, flags);
	rv = csio_mb_isr_handler(hw);
	if (rv == 0 && !(hw->flags & CSIO_HWF_FWEVT_PENDING)) {
		hw->flags |= CSIO_HWF_FWEVT_PENDING;
		spin_unlock_irqrestore(&hw->lock, flags);
		schedule_work(&hw->evtq_work);
		return IRQ_HANDLED;
	}
	spin_unlock_irqrestore(&hw->lock, flags);

	return ret;
}