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
struct lpfc_nvmet_ctx_info {int dummy; } ;
struct TYPE_2__ {int num_present_cpu; struct lpfc_nvmet_ctx_info* nvmet_ctx_info; } ;
struct lpfc_hba {int cfg_nvmet_mrq; TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lpfc_nvmet_clean_io_for_cpu (struct lpfc_hba*,struct lpfc_nvmet_ctx_info*) ; 
 int /*<<< orphan*/  kfree (struct lpfc_nvmet_ctx_info*) ; 

__attribute__((used)) static void
lpfc_nvmet_cleanup_io_context(struct lpfc_hba *phba)
{
	struct lpfc_nvmet_ctx_info *infop;
	int i, j;

	/* The first context list, MRQ 0 CPU 0 */
	infop = phba->sli4_hba.nvmet_ctx_info;
	if (!infop)
		return;

	/* Cycle the the entire CPU context list for every MRQ */
	for (i = 0; i < phba->cfg_nvmet_mrq; i++) {
		for (j = 0; j < phba->sli4_hba.num_present_cpu; j++) {
			__lpfc_nvmet_clean_io_for_cpu(phba, infop);
			infop++; /* next */
		}
	}
	kfree(phba->sli4_hba.nvmet_ctx_info);
	phba->sli4_hba.nvmet_ctx_info = NULL;
}