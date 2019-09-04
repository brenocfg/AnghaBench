#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct lpfc_sli_ring {int dummy; } ;
struct TYPE_2__ {struct lpfc_sli_ring* sli3_ring; } ;
struct lpfc_hba {scalar_t__ intr_type; int hba_flag; int ha_copy; int work_ha_mask; int cfg_multi_ring_support; TYPE_1__ sli; int /*<<< orphan*/  hbalock; int /*<<< orphan*/  HAregaddr; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int DEFER_ERATT ; 
 int HA_R0_CLR_MSK ; 
 int HA_R1_CLR_MSK ; 
 int HA_RXMASK ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int LPFC_EXTRA_RING ; 
 int LPFC_FCP_RING ; 
 scalar_t__ MSIX ; 
 scalar_t__ lpfc_intr_state_check (struct lpfc_hba*) ; 
 scalar_t__ lpfc_readl (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  lpfc_sli_handle_fast_ring_event (struct lpfc_hba*,struct lpfc_sli_ring*,unsigned long) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

irqreturn_t
lpfc_sli_fp_intr_handler(int irq, void *dev_id)
{
	struct lpfc_hba  *phba;
	uint32_t ha_copy;
	unsigned long status;
	unsigned long iflag;
	struct lpfc_sli_ring *pring;

	/* Get the driver's phba structure from the dev_id and
	 * assume the HBA is not interrupting.
	 */
	phba = (struct lpfc_hba *) dev_id;

	if (unlikely(!phba))
		return IRQ_NONE;

	/*
	 * Stuff needs to be attented to when this function is invoked as an
	 * individual interrupt handler in MSI-X multi-message interrupt mode
	 */
	if (phba->intr_type == MSIX) {
		/* Check device state for handling interrupt */
		if (lpfc_intr_state_check(phba))
			return IRQ_NONE;
		/* Need to read HA REG for FCP ring and other ring events */
		if (lpfc_readl(phba->HAregaddr, &ha_copy))
			return IRQ_HANDLED;
		/* Clear up only attention source related to fast-path */
		spin_lock_irqsave(&phba->hbalock, iflag);
		/*
		 * If there is deferred error attention, do not check for
		 * any interrupt.
		 */
		if (unlikely(phba->hba_flag & DEFER_ERATT)) {
			spin_unlock_irqrestore(&phba->hbalock, iflag);
			return IRQ_NONE;
		}
		writel((ha_copy & (HA_R0_CLR_MSK | HA_R1_CLR_MSK)),
			phba->HAregaddr);
		readl(phba->HAregaddr); /* flush */
		spin_unlock_irqrestore(&phba->hbalock, iflag);
	} else
		ha_copy = phba->ha_copy;

	/*
	 * Process all events on FCP ring. Take the optimized path for FCP IO.
	 */
	ha_copy &= ~(phba->work_ha_mask);

	status = (ha_copy & (HA_RXMASK << (4*LPFC_FCP_RING)));
	status >>= (4*LPFC_FCP_RING);
	pring = &phba->sli.sli3_ring[LPFC_FCP_RING];
	if (status & HA_RXMASK)
		lpfc_sli_handle_fast_ring_event(phba, pring, status);

	if (phba->cfg_multi_ring_support == 2) {
		/*
		 * Process all events on extra ring. Take the optimized path
		 * for extra ring IO.
		 */
		status = (ha_copy & (HA_RXMASK << (4*LPFC_EXTRA_RING)));
		status >>= (4*LPFC_EXTRA_RING);
		if (status & HA_RXMASK) {
			lpfc_sli_handle_fast_ring_event(phba,
					&phba->sli.sli3_ring[LPFC_EXTRA_RING],
					status);
		}
	}
	return IRQ_HANDLED;
}