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
struct TYPE_2__ {int /*<<< orphan*/  lpfc_wq_list; struct lpfc_queue** fcp_wq; int /*<<< orphan*/  wq_ecount; int /*<<< orphan*/  wq_esize; struct lpfc_queue** fcp_cq; int /*<<< orphan*/  cq_ecount; int /*<<< orphan*/  cq_esize; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; scalar_t__ fcp_embed_io; scalar_t__ enab_exp_wqcq_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_CQE_EXP_COUNT ; 
 int /*<<< orphan*/  LPFC_DEFAULT_PAGE_SIZE ; 
 int /*<<< orphan*/  LPFC_EXPANDED_PAGE_SIZE ; 
 int /*<<< orphan*/  LPFC_WQE128_SIZE ; 
 int /*<<< orphan*/  LPFC_WQE_EXP_COUNT ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 struct lpfc_queue* lpfc_sli4_queue_alloc (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_alloc_fcp_wq_cq(struct lpfc_hba *phba, int wqidx)
{
	struct lpfc_queue *qdesc;
	uint32_t wqesize;

	/* Create Fast Path FCP CQs */
	if (phba->enab_exp_wqcq_pages)
		/* Increase the CQ size when WQEs contain an embedded cdb */
		qdesc = lpfc_sli4_queue_alloc(phba, LPFC_EXPANDED_PAGE_SIZE,
					      phba->sli4_hba.cq_esize,
					      LPFC_CQE_EXP_COUNT);

	else
		qdesc = lpfc_sli4_queue_alloc(phba, LPFC_DEFAULT_PAGE_SIZE,
					      phba->sli4_hba.cq_esize,
					      phba->sli4_hba.cq_ecount);
	if (!qdesc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"0499 Failed allocate fast-path FCP CQ (%d)\n", wqidx);
		return 1;
	}
	qdesc->qe_valid = 1;
	phba->sli4_hba.fcp_cq[wqidx] = qdesc;

	/* Create Fast Path FCP WQs */
	if (phba->enab_exp_wqcq_pages) {
		/* Increase the WQ size when WQEs contain an embedded cdb */
		wqesize = (phba->fcp_embed_io) ?
			LPFC_WQE128_SIZE : phba->sli4_hba.wq_esize;
		qdesc = lpfc_sli4_queue_alloc(phba, LPFC_EXPANDED_PAGE_SIZE,
					      wqesize,
					      LPFC_WQE_EXP_COUNT);
	} else
		qdesc = lpfc_sli4_queue_alloc(phba, LPFC_DEFAULT_PAGE_SIZE,
					      phba->sli4_hba.wq_esize,
					      phba->sli4_hba.wq_ecount);

	if (!qdesc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0503 Failed allocate fast-path FCP WQ (%d)\n",
				wqidx);
		return 1;
	}
	phba->sli4_hba.fcp_wq[wqidx] = qdesc;
	list_add_tail(&qdesc->wq_list, &phba->sli4_hba.lpfc_wq_list);
	return 0;
}