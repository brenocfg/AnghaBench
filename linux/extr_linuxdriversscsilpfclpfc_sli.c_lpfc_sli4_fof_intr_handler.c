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
struct lpfc_queue {int entry_repost; int EQ_max_eqe; int /*<<< orphan*/  EQ_no_entry; int /*<<< orphan*/  EQ_processed; } ;
struct lpfc_hba_eq_hdl {struct lpfc_hba* phba; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* sli4_eq_release ) (struct lpfc_queue*,int /*<<< orphan*/ ) ;struct lpfc_queue* fof_eq; } ;
struct lpfc_hba {scalar_t__ link_state; scalar_t__ intr_type; TYPE_1__ sli4_hba; int /*<<< orphan*/  hbalock; } ;
struct lpfc_eqe {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_SLI ; 
 scalar_t__ LPFC_LINK_DOWN ; 
 int /*<<< orphan*/  LPFC_QUEUE_REARM ; 
 scalar_t__ MSIX ; 
 int lpfc_intr_state_check (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_sli4_eq_flush (struct lpfc_hba*,struct lpfc_queue*) ; 
 struct lpfc_eqe* lpfc_sli4_eq_get (struct lpfc_queue*) ; 
 int /*<<< orphan*/  lpfc_sli4_fof_handle_eqe (struct lpfc_hba*,struct lpfc_eqe*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct lpfc_queue*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

irqreturn_t
lpfc_sli4_fof_intr_handler(int irq, void *dev_id)
{
	struct lpfc_hba *phba;
	struct lpfc_hba_eq_hdl *hba_eq_hdl;
	struct lpfc_queue *eq;
	struct lpfc_eqe *eqe;
	unsigned long iflag;
	int ecount = 0;

	/* Get the driver's phba structure from the dev_id */
	hba_eq_hdl = (struct lpfc_hba_eq_hdl *)dev_id;
	phba = hba_eq_hdl->phba;

	if (unlikely(!phba))
		return IRQ_NONE;

	/* Get to the EQ struct associated with this vector */
	eq = phba->sli4_hba.fof_eq;
	if (unlikely(!eq))
		return IRQ_NONE;

	/* Check device state for handling interrupt */
	if (unlikely(lpfc_intr_state_check(phba))) {
		/* Check again for link_state with lock held */
		spin_lock_irqsave(&phba->hbalock, iflag);
		if (phba->link_state < LPFC_LINK_DOWN)
			/* Flush, clear interrupt, and rearm the EQ */
			lpfc_sli4_eq_flush(phba, eq);
		spin_unlock_irqrestore(&phba->hbalock, iflag);
		return IRQ_NONE;
	}

	/*
	 * Process all the event on FCP fast-path EQ
	 */
	while ((eqe = lpfc_sli4_eq_get(eq))) {
		lpfc_sli4_fof_handle_eqe(phba, eqe);
		if (!(++ecount % eq->entry_repost))
			break;
		eq->EQ_processed++;
	}

	/* Track the max number of EQEs processed in 1 intr */
	if (ecount > eq->EQ_max_eqe)
		eq->EQ_max_eqe = ecount;


	if (unlikely(ecount == 0)) {
		eq->EQ_no_entry++;

		if (phba->intr_type == MSIX)
			/* MSI-X treated interrupt served as no EQ share INT */
			lpfc_printf_log(phba, KERN_WARNING, LOG_SLI,
					"9145 MSI-X interrupt with no EQE\n");
		else {
			lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
					"9146 ISR interrupt with no EQE\n");
			/* Non MSI-X treated on interrupt as EQ share INT */
			return IRQ_NONE;
		}
	}
	/* Always clear and re-arm the fast-path EQ */
	phba->sli4_hba.sli4_eq_release(eq, LPFC_QUEUE_REARM);
	return IRQ_HANDLED;
}