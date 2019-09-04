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
struct lpfc_sli {struct lpfc_sli_ring* sli3_ring; } ;
struct TYPE_3__ {TYPE_2__** fcp_wq; } ;
struct lpfc_hba {scalar_t__ sli_rev; size_t cfg_fcp_io_channel; TYPE_1__ sli4_hba; struct lpfc_sli sli; } ;
struct TYPE_4__ {struct lpfc_sli_ring* pring; } ;

/* Variables and functions */
 size_t LPFC_FCP_RING ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  lpfc_sli_abort_iocb_ring (struct lpfc_hba*,struct lpfc_sli_ring*) ; 

void
lpfc_sli_abort_fcp_rings(struct lpfc_hba *phba)
{
	struct lpfc_sli *psli = &phba->sli;
	struct lpfc_sli_ring  *pring;
	uint32_t i;

	/* Look on all the FCP Rings for the iotag */
	if (phba->sli_rev >= LPFC_SLI_REV4) {
		for (i = 0; i < phba->cfg_fcp_io_channel; i++) {
			pring = phba->sli4_hba.fcp_wq[i]->pring;
			lpfc_sli_abort_iocb_ring(phba, pring);
		}
	} else {
		pring = &psli->sli3_ring[LPFC_FCP_RING];
		lpfc_sli_abort_iocb_ring(phba, pring);
	}
}