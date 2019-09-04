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
struct TYPE_3__ {int max_eq; } ;
struct TYPE_4__ {int num_online_cpu; int /*<<< orphan*/  cq_ecount; int /*<<< orphan*/  cq_esize; int /*<<< orphan*/  eq_ecount; int /*<<< orphan*/  eq_esize; TYPE_1__ max_cfg_param; } ;
struct lpfc_hba {int io_channel_irqs; int cfg_fcp_io_channel; int cfg_nvme_io_channel; int cfg_nvmet_mrq; TYPE_2__ sli4_hba; scalar_t__ nvmet_support; scalar_t__ cfg_fof; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_CQE_DEF_COUNT ; 
 int /*<<< orphan*/  LPFC_CQE_SIZE ; 
 int /*<<< orphan*/  LPFC_EQE_DEF_COUNT ; 
 int /*<<< orphan*/  LPFC_EQE_SIZE_4B ; 
 scalar_t__ LPFC_NVMET_MRQ_MAX ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,...) ; 

__attribute__((used)) static int
lpfc_sli4_queue_verify(struct lpfc_hba *phba)
{
	int io_channel;
	int fof_vectors = phba->cfg_fof ? 1 : 0;

	/*
	 * Sanity check for configured queue parameters against the run-time
	 * device parameters
	 */

	/* Sanity check on HBA EQ parameters */
	io_channel = phba->io_channel_irqs;

	if (phba->sli4_hba.num_online_cpu < io_channel) {
		lpfc_printf_log(phba,
				KERN_ERR, LOG_INIT,
				"3188 Reducing IO channels to match number of "
				"online CPUs: from %d to %d\n",
				io_channel, phba->sli4_hba.num_online_cpu);
		io_channel = phba->sli4_hba.num_online_cpu;
	}

	if (io_channel + fof_vectors > phba->sli4_hba.max_cfg_param.max_eq) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"2575 Reducing IO channels to match number of "
				"available EQs: from %d to %d\n",
				io_channel,
				phba->sli4_hba.max_cfg_param.max_eq);
		io_channel = phba->sli4_hba.max_cfg_param.max_eq - fof_vectors;
	}

	/* The actual number of FCP / NVME event queues adopted */
	if (io_channel != phba->io_channel_irqs)
		phba->io_channel_irqs = io_channel;
	if (phba->cfg_fcp_io_channel > io_channel)
		phba->cfg_fcp_io_channel = io_channel;
	if (phba->cfg_nvme_io_channel > io_channel)
		phba->cfg_nvme_io_channel = io_channel;
	if (phba->nvmet_support) {
		if (phba->cfg_nvme_io_channel < phba->cfg_nvmet_mrq)
			phba->cfg_nvmet_mrq = phba->cfg_nvme_io_channel;
	}
	if (phba->cfg_nvmet_mrq > LPFC_NVMET_MRQ_MAX)
		phba->cfg_nvmet_mrq = LPFC_NVMET_MRQ_MAX;

	lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"2574 IO channels: irqs %d fcp %d nvme %d MRQ: %d\n",
			phba->io_channel_irqs, phba->cfg_fcp_io_channel,
			phba->cfg_nvme_io_channel, phba->cfg_nvmet_mrq);

	/* Get EQ depth from module parameter, fake the default for now */
	phba->sli4_hba.eq_esize = LPFC_EQE_SIZE_4B;
	phba->sli4_hba.eq_ecount = LPFC_EQE_DEF_COUNT;

	/* Get CQ depth from module parameter, fake the default for now */
	phba->sli4_hba.cq_esize = LPFC_CQE_SIZE;
	phba->sli4_hba.cq_ecount = LPFC_CQE_DEF_COUNT;
	return 0;
}