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
typedef  size_t uint32_t ;
struct lpfc_sli_ring {int dummy; } ;
struct TYPE_4__ {TYPE_1__** nvme_wq; } ;
struct lpfc_hba {scalar_t__ sli_rev; size_t cfg_nvme_io_channel; TYPE_2__ sli4_hba; } ;
struct TYPE_3__ {struct lpfc_sli_ring* pring; } ;

/* Variables and functions */
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  lpfc_sli_abort_wqe_ring (struct lpfc_hba*,struct lpfc_sli_ring*) ; 

void
lpfc_sli_abort_nvme_rings(struct lpfc_hba *phba)
{
	struct lpfc_sli_ring  *pring;
	uint32_t i;

	if (phba->sli_rev < LPFC_SLI_REV4)
		return;

	/* Abort all IO on each NVME ring. */
	for (i = 0; i < phba->cfg_nvme_io_channel; i++) {
		pring = phba->sli4_hba.nvme_wq[i]->pring;
		lpfc_sli_abort_wqe_ring(phba, pring);
	}
}