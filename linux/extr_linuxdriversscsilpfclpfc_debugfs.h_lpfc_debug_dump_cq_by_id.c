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
struct TYPE_3__ {TYPE_2__* mbx_cq; TYPE_2__* nvmels_cq; TYPE_2__* els_cq; TYPE_2__** nvme_cq; TYPE_2__** fcp_cq; } ;
struct lpfc_hba {int cfg_fcp_io_channel; int cfg_nvme_io_channel; TYPE_1__ sli4_hba; } ;
struct TYPE_4__ {int queue_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_debug_dump_q (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 

__attribute__((used)) static inline void
lpfc_debug_dump_cq_by_id(struct lpfc_hba *phba, int qid)
{
	int cq_idx;

	for (cq_idx = 0; cq_idx < phba->cfg_fcp_io_channel; cq_idx++)
		if (phba->sli4_hba.fcp_cq[cq_idx]->queue_id == qid)
			break;

	if (cq_idx < phba->cfg_fcp_io_channel) {
		pr_err("FCP CQ[Idx:%d|Qid:%d]\n", cq_idx, qid);
		lpfc_debug_dump_q(phba->sli4_hba.fcp_cq[cq_idx]);
		return;
	}

	for (cq_idx = 0; cq_idx < phba->cfg_nvme_io_channel; cq_idx++)
		if (phba->sli4_hba.nvme_cq[cq_idx]->queue_id == qid)
			break;

	if (cq_idx < phba->cfg_nvme_io_channel) {
		pr_err("NVME CQ[Idx:%d|Qid:%d]\n", cq_idx, qid);
		lpfc_debug_dump_q(phba->sli4_hba.nvme_cq[cq_idx]);
		return;
	}

	if (phba->sli4_hba.els_cq->queue_id == qid) {
		pr_err("ELS CQ[Qid:%d]\n", qid);
		lpfc_debug_dump_q(phba->sli4_hba.els_cq);
		return;
	}

	if (phba->sli4_hba.nvmels_cq->queue_id == qid) {
		pr_err("NVME LS CQ[Qid:%d]\n", qid);
		lpfc_debug_dump_q(phba->sli4_hba.nvmels_cq);
		return;
	}

	if (phba->sli4_hba.mbx_cq->queue_id == qid) {
		pr_err("MBX CQ[Qid:%d]\n", qid);
		lpfc_debug_dump_q(phba->sli4_hba.mbx_cq);
	}
}