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
struct TYPE_2__ {int /*<<< orphan*/ * oas_wq; int /*<<< orphan*/ * oas_cq; int /*<<< orphan*/ * fof_eq; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_sli4_queue_free (int /*<<< orphan*/ *) ; 

int
lpfc_fof_queue_destroy(struct lpfc_hba *phba)
{
	/* Release FOF Event queue */
	if (phba->sli4_hba.fof_eq != NULL) {
		lpfc_sli4_queue_free(phba->sli4_hba.fof_eq);
		phba->sli4_hba.fof_eq = NULL;
	}

	/* Release OAS Completion queue */
	if (phba->sli4_hba.oas_cq != NULL) {
		lpfc_sli4_queue_free(phba->sli4_hba.oas_cq);
		phba->sli4_hba.oas_cq = NULL;
	}

	/* Release OAS Work queue */
	if (phba->sli4_hba.oas_wq != NULL) {
		lpfc_sli4_queue_free(phba->sli4_hba.oas_wq);
		phba->sli4_hba.oas_wq = NULL;
	}
	return 0;
}