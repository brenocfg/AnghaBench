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
struct lpfc_sli4_hba {int /*<<< orphan*/  fof_eq; int /*<<< orphan*/  (* sli4_eq_release ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__* nvmet_cqset; int /*<<< orphan*/  (* sli4_cq_release ) (scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * hba_eq; scalar_t__ oas_cq; scalar_t__* nvme_cq; scalar_t__* fcp_cq; scalar_t__ nvmels_cq; scalar_t__ els_cq; scalar_t__ mbx_cq; } ;
struct lpfc_hba {int cfg_fcp_io_channel; int cfg_nvme_io_channel; int io_channel_irqs; int cfg_nvmet_mrq; scalar_t__ cfg_fof; scalar_t__ nvmet_support; struct lpfc_sli4_hba sli4_hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPFC_QUEUE_REARM ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_sli4_arm_cqeq_intr(struct lpfc_hba *phba)
{
	int qidx;
	struct lpfc_sli4_hba *sli4_hba = &phba->sli4_hba;

	sli4_hba->sli4_cq_release(sli4_hba->mbx_cq, LPFC_QUEUE_REARM);
	sli4_hba->sli4_cq_release(sli4_hba->els_cq, LPFC_QUEUE_REARM);
	if (sli4_hba->nvmels_cq)
		sli4_hba->sli4_cq_release(sli4_hba->nvmels_cq,
						LPFC_QUEUE_REARM);

	if (sli4_hba->fcp_cq)
		for (qidx = 0; qidx < phba->cfg_fcp_io_channel; qidx++)
			sli4_hba->sli4_cq_release(sli4_hba->fcp_cq[qidx],
						LPFC_QUEUE_REARM);

	if (sli4_hba->nvme_cq)
		for (qidx = 0; qidx < phba->cfg_nvme_io_channel; qidx++)
			sli4_hba->sli4_cq_release(sli4_hba->nvme_cq[qidx],
						LPFC_QUEUE_REARM);

	if (phba->cfg_fof)
		sli4_hba->sli4_cq_release(sli4_hba->oas_cq, LPFC_QUEUE_REARM);

	if (sli4_hba->hba_eq)
		for (qidx = 0; qidx < phba->io_channel_irqs; qidx++)
			sli4_hba->sli4_eq_release(sli4_hba->hba_eq[qidx],
							LPFC_QUEUE_REARM);

	if (phba->nvmet_support) {
		for (qidx = 0; qidx < phba->cfg_nvmet_mrq; qidx++) {
			sli4_hba->sli4_cq_release(
				sli4_hba->nvmet_cqset[qidx],
				LPFC_QUEUE_REARM);
		}
	}

	if (phba->cfg_fof)
		sli4_hba->sli4_eq_release(sli4_hba->fof_eq, LPFC_QUEUE_REARM);
}