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
struct lpfc_queue {int qe_valid; int /*<<< orphan*/  wq_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lpfc_wq_list; struct lpfc_queue** nvme_wq; struct lpfc_queue** nvme_cq; int /*<<< orphan*/  cq_esize; } ;
struct lpfc_hba {TYPE_1__ sli4_hba; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_CQE_EXP_COUNT ; 
 int /*<<< orphan*/  LPFC_EXPANDED_PAGE_SIZE ; 
 int /*<<< orphan*/  LPFC_WQE128_SIZE ; 
 int /*<<< orphan*/  LPFC_WQE_EXP_COUNT ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 struct lpfc_queue* lpfc_sli4_queue_alloc (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_alloc_nvme_wq_cq(struct lpfc_hba *phba, int wqidx)
{
	struct lpfc_queue *qdesc;

	qdesc = lpfc_sli4_queue_alloc(phba, LPFC_EXPANDED_PAGE_SIZE,
				      phba->sli4_hba.cq_esize,
				      LPFC_CQE_EXP_COUNT);
	if (!qdesc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0508 Failed allocate fast-path NVME CQ (%d)\n",
				wqidx);
		return 1;
	}
	qdesc->qe_valid = 1;
	phba->sli4_hba.nvme_cq[wqidx] = qdesc;

	qdesc = lpfc_sli4_queue_alloc(phba, LPFC_EXPANDED_PAGE_SIZE,
				      LPFC_WQE128_SIZE, LPFC_WQE_EXP_COUNT);
	if (!qdesc) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0509 Failed allocate fast-path NVME WQ (%d)\n",
				wqidx);
		return 1;
	}
	phba->sli4_hba.nvme_wq[wqidx] = qdesc;
	list_add_tail(&qdesc->wq_list, &phba->sli4_hba.lpfc_wq_list);
	return 0;
}