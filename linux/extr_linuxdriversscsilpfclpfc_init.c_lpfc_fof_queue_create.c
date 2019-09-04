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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_queue {int qe_valid; int /*<<< orphan*/  wq_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lpfc_wq_list; struct lpfc_queue* oas_wq; int /*<<< orphan*/  wq_ecount; int /*<<< orphan*/  wq_esize; struct lpfc_queue* oas_cq; int /*<<< orphan*/  cq_ecount; int /*<<< orphan*/  cq_esize; struct lpfc_queue* fof_eq; int /*<<< orphan*/  eq_ecount; int /*<<< orphan*/  eq_esize; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; scalar_t__ fcp_embed_io; scalar_t__ enab_exp_wqcq_pages; scalar_t__ cfg_fof; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LPFC_CQE_EXP_COUNT ; 
 int /*<<< orphan*/  LPFC_DEFAULT_PAGE_SIZE ; 
 int /*<<< orphan*/  LPFC_EXPANDED_PAGE_SIZE ; 
 int /*<<< orphan*/  LPFC_WQE128_SIZE ; 
 int /*<<< orphan*/  LPFC_WQE_EXP_COUNT ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_fof_queue_destroy (struct lpfc_hba*) ; 
 struct lpfc_queue* lpfc_sli4_queue_alloc (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
lpfc_fof_queue_create(struct lpfc_hba *phba)
{
	struct lpfc_queue *qdesc;
	uint32_t wqesize;

	/* Create FOF EQ */
	qdesc = lpfc_sli4_queue_alloc(phba, LPFC_DEFAULT_PAGE_SIZE,
				      phba->sli4_hba.eq_esize,
				      phba->sli4_hba.eq_ecount);
	if (!qdesc)
		goto out_error;

	qdesc->qe_valid = 1;
	phba->sli4_hba.fof_eq = qdesc;

	if (phba->cfg_fof) {

		/* Create OAS CQ */
		if (phba->enab_exp_wqcq_pages)
			qdesc = lpfc_sli4_queue_alloc(phba,
						      LPFC_EXPANDED_PAGE_SIZE,
						      phba->sli4_hba.cq_esize,
						      LPFC_CQE_EXP_COUNT);
		else
			qdesc = lpfc_sli4_queue_alloc(phba,
						      LPFC_DEFAULT_PAGE_SIZE,
						      phba->sli4_hba.cq_esize,
						      phba->sli4_hba.cq_ecount);
		if (!qdesc)
			goto out_error;

		qdesc->qe_valid = 1;
		phba->sli4_hba.oas_cq = qdesc;

		/* Create OAS WQ */
		if (phba->enab_exp_wqcq_pages) {
			wqesize = (phba->fcp_embed_io) ?
				LPFC_WQE128_SIZE : phba->sli4_hba.wq_esize;
			qdesc = lpfc_sli4_queue_alloc(phba,
						      LPFC_EXPANDED_PAGE_SIZE,
						      wqesize,
						      LPFC_WQE_EXP_COUNT);
		} else
			qdesc = lpfc_sli4_queue_alloc(phba,
						      LPFC_DEFAULT_PAGE_SIZE,
						      phba->sli4_hba.wq_esize,
						      phba->sli4_hba.wq_ecount);

		if (!qdesc)
			goto out_error;

		phba->sli4_hba.oas_wq = qdesc;
		list_add_tail(&qdesc->wq_list, &phba->sli4_hba.lpfc_wq_list);

	}
	return 0;

out_error:
	lpfc_fof_queue_destroy(phba);
	return -ENOMEM;
}