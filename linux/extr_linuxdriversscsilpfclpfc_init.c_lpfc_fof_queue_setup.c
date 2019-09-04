#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* wqp; } ;
struct TYPE_9__ {TYPE_1__ sli4; } ;
struct lpfc_sli_ring {TYPE_2__ sli; } ;
struct TYPE_10__ {int /*<<< orphan*/  fof_eq; TYPE_5__* oas_cq; TYPE_4__* oas_wq; } ;
struct lpfc_hba {TYPE_3__ sli4_hba; scalar_t__ cfg_fof; } ;
struct TYPE_12__ {struct lpfc_sli_ring* pring; } ;
struct TYPE_11__ {struct lpfc_sli_ring* pring; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LPFC_FCP ; 
 int /*<<< orphan*/  LPFC_MAX_IMAX ; 
 int /*<<< orphan*/  LPFC_WCQ ; 
 int lpfc_cq_create (struct lpfc_hba*,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_cq_destroy (struct lpfc_hba*,TYPE_5__*) ; 
 int lpfc_eq_create (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_eq_destroy (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int lpfc_wq_create (struct lpfc_hba*,TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ) ; 

int
lpfc_fof_queue_setup(struct lpfc_hba *phba)
{
	struct lpfc_sli_ring *pring;
	int rc;

	rc = lpfc_eq_create(phba, phba->sli4_hba.fof_eq, LPFC_MAX_IMAX);
	if (rc)
		return -ENOMEM;

	if (phba->cfg_fof) {

		rc = lpfc_cq_create(phba, phba->sli4_hba.oas_cq,
				    phba->sli4_hba.fof_eq, LPFC_WCQ, LPFC_FCP);
		if (rc)
			goto out_oas_cq;

		rc = lpfc_wq_create(phba, phba->sli4_hba.oas_wq,
				    phba->sli4_hba.oas_cq, LPFC_FCP);
		if (rc)
			goto out_oas_wq;

		/* Bind this CQ/WQ to the NVME ring */
		pring = phba->sli4_hba.oas_wq->pring;
		pring->sli.sli4.wqp =
			(void *)phba->sli4_hba.oas_wq;
		phba->sli4_hba.oas_cq->pring = pring;
	}

	return 0;

out_oas_wq:
	lpfc_cq_destroy(phba, phba->sli4_hba.oas_cq);
out_oas_cq:
	lpfc_eq_destroy(phba, phba->sli4_hba.fof_eq);
	return rc;

}