#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {TYPE_2__* nvmels_wq; TYPE_2__* els_wq; TYPE_2__** nvme_wq; TYPE_2__** fcp_wq; } ;
struct lpfc_hba {int cfg_fcp_io_channel; int cfg_nvme_io_channel; TYPE_1__ sli4_hba; } ;
struct TYPE_4__ {int queue_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_debug_dump_q (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 

__attribute__((used)) static inline void
lpfc_debug_dump_wq_by_id(struct lpfc_hba *phba, int qid)
{
	int wq_idx;

	for (wq_idx = 0; wq_idx < phba->cfg_fcp_io_channel; wq_idx++)
		if (phba->sli4_hba.fcp_wq[wq_idx]->queue_id == qid)
			break;
	if (wq_idx < phba->cfg_fcp_io_channel) {
		pr_err("FCP WQ[Idx:%d|Qid:%d]\n", wq_idx, qid);
		lpfc_debug_dump_q(phba->sli4_hba.fcp_wq[wq_idx]);
		return;
	}

	for (wq_idx = 0; wq_idx < phba->cfg_nvme_io_channel; wq_idx++)
		if (phba->sli4_hba.nvme_wq[wq_idx]->queue_id == qid)
			break;
	if (wq_idx < phba->cfg_nvme_io_channel) {
		pr_err("NVME WQ[Idx:%d|Qid:%d]\n", wq_idx, qid);
		lpfc_debug_dump_q(phba->sli4_hba.nvme_wq[wq_idx]);
		return;
	}

	if (phba->sli4_hba.els_wq->queue_id == qid) {
		pr_err("ELS WQ[Qid:%d]\n", qid);
		lpfc_debug_dump_q(phba->sli4_hba.els_wq);
		return;
	}

	if (phba->sli4_hba.nvmels_wq->queue_id == qid) {
		pr_err("NVME LS WQ[Qid:%d]\n", qid);
		lpfc_debug_dump_q(phba->sli4_hba.nvmels_wq);
	}
}