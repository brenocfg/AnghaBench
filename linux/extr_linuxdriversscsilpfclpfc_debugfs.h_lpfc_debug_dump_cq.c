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
struct lpfc_queue {scalar_t__ assoc_qid; scalar_t__ queue_id; } ;
struct TYPE_2__ {struct lpfc_queue** hba_eq; struct lpfc_queue* nvmels_cq; struct lpfc_queue* nvmels_wq; struct lpfc_queue* els_cq; struct lpfc_queue* els_wq; struct lpfc_queue* mbx_cq; struct lpfc_queue* mbx_wq; struct lpfc_queue** nvme_cq; struct lpfc_queue** nvme_wq; struct lpfc_queue** fcp_cq; struct lpfc_queue** fcp_wq; } ;
struct lpfc_hba {int io_channel_irqs; TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int DUMP_ELS ; 
 int DUMP_FCP ; 
 int DUMP_MBX ; 
 int DUMP_NVME ; 
 int DUMP_NVMELS ; 
 int /*<<< orphan*/  lpfc_debug_dump_q (struct lpfc_queue*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static inline void
lpfc_debug_dump_cq(struct lpfc_hba *phba, int qtype, int wqidx)
{
	struct lpfc_queue *wq, *cq, *eq;
	char *qtypestr;
	int eqidx;

	/* fcp/nvme wq and cq are 1:1, thus same indexes */

	if (qtype == DUMP_FCP) {
		wq = phba->sli4_hba.fcp_wq[wqidx];
		cq = phba->sli4_hba.fcp_cq[wqidx];
		qtypestr = "FCP";
	} else if (qtype == DUMP_NVME) {
		wq = phba->sli4_hba.nvme_wq[wqidx];
		cq = phba->sli4_hba.nvme_cq[wqidx];
		qtypestr = "NVME";
	} else if (qtype == DUMP_MBX) {
		wq = phba->sli4_hba.mbx_wq;
		cq = phba->sli4_hba.mbx_cq;
		qtypestr = "MBX";
	} else if (qtype == DUMP_ELS) {
		wq = phba->sli4_hba.els_wq;
		cq = phba->sli4_hba.els_cq;
		qtypestr = "ELS";
	} else if (qtype == DUMP_NVMELS) {
		wq = phba->sli4_hba.nvmels_wq;
		cq = phba->sli4_hba.nvmels_cq;
		qtypestr = "NVMELS";
	} else
		return;

	for (eqidx = 0; eqidx < phba->io_channel_irqs; eqidx++) {
		if (cq->assoc_qid == phba->sli4_hba.hba_eq[eqidx]->queue_id)
			break;
	}
	if (eqidx == phba->io_channel_irqs) {
		pr_err("Couldn't find EQ for CQ. Using EQ[0]\n");
		eqidx = 0;
	}

	eq = phba->sli4_hba.hba_eq[eqidx];

	if (qtype == DUMP_FCP || qtype == DUMP_NVME)
		pr_err("%s CQ: WQ[Idx:%d|Qid%d]->CQ[Idx%d|Qid%d]"
			"->EQ[Idx:%d|Qid:%d]:\n",
			qtypestr, wqidx, wq->queue_id, wqidx, cq->queue_id,
			eqidx, eq->queue_id);
	else
		pr_err("%s CQ: WQ[Qid:%d]->CQ[Qid:%d]"
			"->EQ[Idx:%d|Qid:%d]:\n",
			qtypestr, wq->queue_id, cq->queue_id,
			eqidx, eq->queue_id);

	lpfc_debug_dump_q(cq);
}