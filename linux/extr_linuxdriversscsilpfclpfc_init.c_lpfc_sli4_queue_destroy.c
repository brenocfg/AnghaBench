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
struct TYPE_2__ {int /*<<< orphan*/  lpfc_wq_list; int /*<<< orphan*/  mbx_cq; int /*<<< orphan*/  nvmels_cq; int /*<<< orphan*/  els_cq; int /*<<< orphan*/  dat_rq; int /*<<< orphan*/  hdr_rq; int /*<<< orphan*/  nvmels_wq; int /*<<< orphan*/  els_wq; int /*<<< orphan*/  mbx_wq; int /*<<< orphan*/  nvmet_mrq_data; int /*<<< orphan*/  nvmet_mrq_hdr; int /*<<< orphan*/  nvmet_cqset; int /*<<< orphan*/  nvme_cq_map; int /*<<< orphan*/  nvme_wq; int /*<<< orphan*/  nvme_cq; int /*<<< orphan*/  fcp_cq_map; int /*<<< orphan*/  fcp_wq; int /*<<< orphan*/  fcp_cq; int /*<<< orphan*/  hba_eq; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; int /*<<< orphan*/  cfg_nvmet_mrq; scalar_t__ nvmet_support; int /*<<< orphan*/  cfg_nvme_io_channel; int /*<<< orphan*/  cfg_fcp_io_channel; int /*<<< orphan*/  io_channel_irqs; scalar_t__ cfg_fof; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lpfc_sli4_release_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_fof_queue_destroy (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli4_release_queue_map (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_sli4_release_queues (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
lpfc_sli4_queue_destroy(struct lpfc_hba *phba)
{
	if (phba->cfg_fof)
		lpfc_fof_queue_destroy(phba);

	/* Release HBA eqs */
	lpfc_sli4_release_queues(&phba->sli4_hba.hba_eq, phba->io_channel_irqs);

	/* Release FCP cqs */
	lpfc_sli4_release_queues(&phba->sli4_hba.fcp_cq,
				 phba->cfg_fcp_io_channel);

	/* Release FCP wqs */
	lpfc_sli4_release_queues(&phba->sli4_hba.fcp_wq,
				 phba->cfg_fcp_io_channel);

	/* Release FCP CQ mapping array */
	lpfc_sli4_release_queue_map(&phba->sli4_hba.fcp_cq_map);

	/* Release NVME cqs */
	lpfc_sli4_release_queues(&phba->sli4_hba.nvme_cq,
					phba->cfg_nvme_io_channel);

	/* Release NVME wqs */
	lpfc_sli4_release_queues(&phba->sli4_hba.nvme_wq,
					phba->cfg_nvme_io_channel);

	/* Release NVME CQ mapping array */
	lpfc_sli4_release_queue_map(&phba->sli4_hba.nvme_cq_map);

	if (phba->nvmet_support) {
		lpfc_sli4_release_queues(&phba->sli4_hba.nvmet_cqset,
					 phba->cfg_nvmet_mrq);

		lpfc_sli4_release_queues(&phba->sli4_hba.nvmet_mrq_hdr,
					 phba->cfg_nvmet_mrq);
		lpfc_sli4_release_queues(&phba->sli4_hba.nvmet_mrq_data,
					 phba->cfg_nvmet_mrq);
	}

	/* Release mailbox command work queue */
	__lpfc_sli4_release_queue(&phba->sli4_hba.mbx_wq);

	/* Release ELS work queue */
	__lpfc_sli4_release_queue(&phba->sli4_hba.els_wq);

	/* Release ELS work queue */
	__lpfc_sli4_release_queue(&phba->sli4_hba.nvmels_wq);

	/* Release unsolicited receive queue */
	__lpfc_sli4_release_queue(&phba->sli4_hba.hdr_rq);
	__lpfc_sli4_release_queue(&phba->sli4_hba.dat_rq);

	/* Release ELS complete queue */
	__lpfc_sli4_release_queue(&phba->sli4_hba.els_cq);

	/* Release NVME LS complete queue */
	__lpfc_sli4_release_queue(&phba->sli4_hba.nvmels_cq);

	/* Release mailbox command complete queue */
	__lpfc_sli4_release_queue(&phba->sli4_hba.mbx_cq);

	/* Everything on this list has been freed */
	INIT_LIST_HEAD(&phba->sli4_hba.lpfc_wq_list);
}