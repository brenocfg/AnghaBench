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
typedef  size_t uint32_t ;
struct lpfc_sli4_hba {int /*<<< orphan*/  (* sli4_eq_release ) (struct lpfc_queue*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* sli4_eq_clr_intr ) (struct lpfc_queue*) ;struct lpfc_queue** hba_eq; TYPE_1__* mbx_cq; } ;
struct lpfc_queue {scalar_t__ queue_id; int /*<<< orphan*/  EQ_processed; } ;
struct lpfc_hba {scalar_t__ sli_rev; size_t io_channel_irqs; struct lpfc_sli4_hba sli4_hba; } ;
struct lpfc_eqe {int dummy; } ;
struct TYPE_2__ {scalar_t__ assoc_qid; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_QUEUE_REARM ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 struct lpfc_eqe* lpfc_sli4_eq_get (struct lpfc_queue*) ; 
 int /*<<< orphan*/  lpfc_sli4_hba_handle_eqe (struct lpfc_hba*,struct lpfc_eqe*,size_t) ; 
 int lpfc_sli4_mbox_completions_pending (struct lpfc_hba*) ; 
 int /*<<< orphan*/  stub1 (struct lpfc_queue*) ; 
 int /*<<< orphan*/  stub2 (struct lpfc_queue*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

bool
lpfc_sli4_process_missed_mbox_completions(struct lpfc_hba *phba)
{
	struct lpfc_sli4_hba *sli4_hba = &phba->sli4_hba;
	uint32_t eqidx;
	struct lpfc_queue *fpeq = NULL;
	struct lpfc_eqe *eqe;
	bool mbox_pending;

	if (unlikely(!phba) || (phba->sli_rev != LPFC_SLI_REV4))
		return false;

	/* Find the eq associated with the mcq */

	if (sli4_hba->hba_eq)
		for (eqidx = 0; eqidx < phba->io_channel_irqs; eqidx++)
			if (sli4_hba->hba_eq[eqidx]->queue_id ==
			    sli4_hba->mbx_cq->assoc_qid) {
				fpeq = sli4_hba->hba_eq[eqidx];
				break;
			}
	if (!fpeq)
		return false;

	/* Turn off interrupts from this EQ */

	sli4_hba->sli4_eq_clr_intr(fpeq);

	/* Check to see if a mbox completion is pending */

	mbox_pending = lpfc_sli4_mbox_completions_pending(phba);

	/*
	 * If a mbox completion is pending, process all the events on EQ
	 * associated with the mbox completion queue (this could include
	 * mailbox commands, async events, els commands, receive queue data
	 * and fcp commands)
	 */

	if (mbox_pending)
		while ((eqe = lpfc_sli4_eq_get(fpeq))) {
			lpfc_sli4_hba_handle_eqe(phba, eqe, eqidx);
			fpeq->EQ_processed++;
		}

	/* Always clear and re-arm the EQ */

	sli4_hba->sli4_eq_release(fpeq, LPFC_QUEUE_REARM);

	return mbox_pending;

}