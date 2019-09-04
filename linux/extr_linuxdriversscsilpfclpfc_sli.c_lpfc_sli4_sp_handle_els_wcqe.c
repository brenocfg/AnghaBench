#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct lpfc_wcqe_complete {int /*<<< orphan*/  word3; int /*<<< orphan*/  parameter; int /*<<< orphan*/  total_data_placed; int /*<<< orphan*/  word0; } ;
struct lpfc_sli_ring {int /*<<< orphan*/  txcmplq; int /*<<< orphan*/  txq; } ;
struct lpfc_queue {struct lpfc_sli_ring* pring; } ;
struct TYPE_4__ {int /*<<< orphan*/  wcqe_cmpl; } ;
struct TYPE_5__ {int /*<<< orphan*/  list; TYPE_1__ cqe; } ;
struct lpfc_iocbq {TYPE_2__ cq_event; } ;
struct TYPE_6__ {int /*<<< orphan*/  sp_queue_event; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; int /*<<< orphan*/  hba_flag; TYPE_3__ sli4_hba; int /*<<< orphan*/  iocb_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  HBA_SP_QUEUE_EVT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_SLI ; 
 int /*<<< orphan*/  bf_get (int /*<<< orphan*/ ,struct lpfc_wcqe_complete*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int,int,...) ; 
 struct lpfc_iocbq* lpfc_sli_get_iocbq (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_wcqe_c_status ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct lpfc_wcqe_complete*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
lpfc_sli4_sp_handle_els_wcqe(struct lpfc_hba *phba, struct lpfc_queue *cq,
			     struct lpfc_wcqe_complete *wcqe)
{
	struct lpfc_iocbq *irspiocbq;
	unsigned long iflags;
	struct lpfc_sli_ring *pring = cq->pring;
	int txq_cnt = 0;
	int txcmplq_cnt = 0;
	int fcp_txcmplq_cnt = 0;

	/* Check for response status */
	if (unlikely(bf_get(lpfc_wcqe_c_status, wcqe))) {
		/* Log the error status */
		lpfc_printf_log(phba, KERN_INFO, LOG_SLI,
				"0357 ELS CQE error: status=x%x: "
				"CQE: %08x %08x %08x %08x\n",
				bf_get(lpfc_wcqe_c_status, wcqe),
				wcqe->word0, wcqe->total_data_placed,
				wcqe->parameter, wcqe->word3);
	}

	/* Get an irspiocbq for later ELS response processing use */
	irspiocbq = lpfc_sli_get_iocbq(phba);
	if (!irspiocbq) {
		if (!list_empty(&pring->txq))
			txq_cnt++;
		if (!list_empty(&pring->txcmplq))
			txcmplq_cnt++;
		lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
			"0387 NO IOCBQ data: txq_cnt=%d iocb_cnt=%d "
			"fcp_txcmplq_cnt=%d, els_txcmplq_cnt=%d\n",
			txq_cnt, phba->iocb_cnt,
			fcp_txcmplq_cnt,
			txcmplq_cnt);
		return false;
	}

	/* Save off the slow-path queue event for work thread to process */
	memcpy(&irspiocbq->cq_event.cqe.wcqe_cmpl, wcqe, sizeof(*wcqe));
	spin_lock_irqsave(&phba->hbalock, iflags);
	list_add_tail(&irspiocbq->cq_event.list,
		      &phba->sli4_hba.sp_queue_event);
	phba->hba_flag |= HBA_SP_QUEUE_EVT;
	spin_unlock_irqrestore(&phba->hbalock, iflags);

	return true;
}