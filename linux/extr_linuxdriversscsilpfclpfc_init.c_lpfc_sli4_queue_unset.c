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
struct TYPE_2__ {int /*<<< orphan*/ * hba_eq; scalar_t__* fcp_cq; scalar_t__* nvmet_cqset; int /*<<< orphan*/ * nvmet_mrq_data; scalar_t__* nvmet_mrq_hdr; scalar_t__* nvme_cq; scalar_t__ nvmels_cq; scalar_t__ els_cq; scalar_t__ mbx_cq; scalar_t__* nvme_wq; scalar_t__* fcp_wq; int /*<<< orphan*/  dat_rq; scalar_t__ hdr_rq; scalar_t__ els_wq; scalar_t__ nvmels_wq; scalar_t__ mbx_wq; } ;
struct lpfc_hba {int cfg_fcp_io_channel; int cfg_nvme_io_channel; int cfg_nvmet_mrq; int io_channel_irqs; TYPE_1__ sli4_hba; scalar_t__ nvmet_support; scalar_t__ cfg_fof; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_cq_destroy (struct lpfc_hba*,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_eq_destroy (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_fof_queue_destroy (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_mq_destroy (struct lpfc_hba*,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_rq_destroy (struct lpfc_hba*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_wq_destroy (struct lpfc_hba*,scalar_t__) ; 

void
lpfc_sli4_queue_unset(struct lpfc_hba *phba)
{
	int qidx;

	/* Unset the queues created for Flash Optimized Fabric operations */
	if (phba->cfg_fof)
		lpfc_fof_queue_destroy(phba);

	/* Unset mailbox command work queue */
	if (phba->sli4_hba.mbx_wq)
		lpfc_mq_destroy(phba, phba->sli4_hba.mbx_wq);

	/* Unset NVME LS work queue */
	if (phba->sli4_hba.nvmels_wq)
		lpfc_wq_destroy(phba, phba->sli4_hba.nvmels_wq);

	/* Unset ELS work queue */
	if (phba->sli4_hba.els_wq)
		lpfc_wq_destroy(phba, phba->sli4_hba.els_wq);

	/* Unset unsolicited receive queue */
	if (phba->sli4_hba.hdr_rq)
		lpfc_rq_destroy(phba, phba->sli4_hba.hdr_rq,
				phba->sli4_hba.dat_rq);

	/* Unset FCP work queue */
	if (phba->sli4_hba.fcp_wq)
		for (qidx = 0; qidx < phba->cfg_fcp_io_channel; qidx++)
			lpfc_wq_destroy(phba, phba->sli4_hba.fcp_wq[qidx]);

	/* Unset NVME work queue */
	if (phba->sli4_hba.nvme_wq) {
		for (qidx = 0; qidx < phba->cfg_nvme_io_channel; qidx++)
			lpfc_wq_destroy(phba, phba->sli4_hba.nvme_wq[qidx]);
	}

	/* Unset mailbox command complete queue */
	if (phba->sli4_hba.mbx_cq)
		lpfc_cq_destroy(phba, phba->sli4_hba.mbx_cq);

	/* Unset ELS complete queue */
	if (phba->sli4_hba.els_cq)
		lpfc_cq_destroy(phba, phba->sli4_hba.els_cq);

	/* Unset NVME LS complete queue */
	if (phba->sli4_hba.nvmels_cq)
		lpfc_cq_destroy(phba, phba->sli4_hba.nvmels_cq);

	/* Unset NVME response complete queue */
	if (phba->sli4_hba.nvme_cq)
		for (qidx = 0; qidx < phba->cfg_nvme_io_channel; qidx++)
			lpfc_cq_destroy(phba, phba->sli4_hba.nvme_cq[qidx]);

	if (phba->nvmet_support) {
		/* Unset NVMET MRQ queue */
		if (phba->sli4_hba.nvmet_mrq_hdr) {
			for (qidx = 0; qidx < phba->cfg_nvmet_mrq; qidx++)
				lpfc_rq_destroy(
					phba,
					phba->sli4_hba.nvmet_mrq_hdr[qidx],
					phba->sli4_hba.nvmet_mrq_data[qidx]);
		}

		/* Unset NVMET CQ Set complete queue */
		if (phba->sli4_hba.nvmet_cqset) {
			for (qidx = 0; qidx < phba->cfg_nvmet_mrq; qidx++)
				lpfc_cq_destroy(
					phba, phba->sli4_hba.nvmet_cqset[qidx]);
		}
	}

	/* Unset FCP response complete queue */
	if (phba->sli4_hba.fcp_cq)
		for (qidx = 0; qidx < phba->cfg_fcp_io_channel; qidx++)
			lpfc_cq_destroy(phba, phba->sli4_hba.fcp_cq[qidx]);

	/* Unset fast-path event queue */
	if (phba->sli4_hba.hba_eq)
		for (qidx = 0; qidx < phba->io_channel_irqs; qidx++)
			lpfc_eq_destroy(phba, phba->sli4_hba.hba_eq[qidx]);
}