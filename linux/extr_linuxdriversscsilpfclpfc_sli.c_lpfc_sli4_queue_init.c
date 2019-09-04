#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct lpfc_sli_ring {int /*<<< orphan*/  ring_lock; int /*<<< orphan*/  iocb_continueq; int /*<<< orphan*/  txcmplq; int /*<<< orphan*/  txq; void* ringno; scalar_t__ flag; } ;
struct lpfc_sli {int /*<<< orphan*/  mboxq_cmpl; int /*<<< orphan*/  mboxq; } ;
struct TYPE_12__ {TYPE_5__* oas_wq; TYPE_4__* nvmels_wq; TYPE_3__* els_wq; TYPE_2__** nvme_wq; TYPE_1__** fcp_wq; } ;
struct lpfc_hba {int cfg_fcp_io_channel; int cfg_nvme_io_channel; int /*<<< orphan*/  hbalock; TYPE_6__ sli4_hba; scalar_t__ cfg_fof; struct lpfc_sli sli; } ;
struct TYPE_11__ {struct lpfc_sli_ring* pring; } ;
struct TYPE_10__ {struct lpfc_sli_ring* pring; } ;
struct TYPE_9__ {struct lpfc_sli_ring* pring; } ;
struct TYPE_8__ {struct lpfc_sli_ring* pring; } ;
struct TYPE_7__ {struct lpfc_sli_ring* pring; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* LPFC_ELS_RING ; 
 void* LPFC_FCP_RING ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void
lpfc_sli4_queue_init(struct lpfc_hba *phba)
{
	struct lpfc_sli *psli;
	struct lpfc_sli_ring *pring;
	int i;

	psli = &phba->sli;
	spin_lock_irq(&phba->hbalock);
	INIT_LIST_HEAD(&psli->mboxq);
	INIT_LIST_HEAD(&psli->mboxq_cmpl);
	/* Initialize list headers for txq and txcmplq as double linked lists */
	for (i = 0; i < phba->cfg_fcp_io_channel; i++) {
		pring = phba->sli4_hba.fcp_wq[i]->pring;
		pring->flag = 0;
		pring->ringno = LPFC_FCP_RING;
		INIT_LIST_HEAD(&pring->txq);
		INIT_LIST_HEAD(&pring->txcmplq);
		INIT_LIST_HEAD(&pring->iocb_continueq);
		spin_lock_init(&pring->ring_lock);
	}
	for (i = 0; i < phba->cfg_nvme_io_channel; i++) {
		pring = phba->sli4_hba.nvme_wq[i]->pring;
		pring->flag = 0;
		pring->ringno = LPFC_FCP_RING;
		INIT_LIST_HEAD(&pring->txq);
		INIT_LIST_HEAD(&pring->txcmplq);
		INIT_LIST_HEAD(&pring->iocb_continueq);
		spin_lock_init(&pring->ring_lock);
	}
	pring = phba->sli4_hba.els_wq->pring;
	pring->flag = 0;
	pring->ringno = LPFC_ELS_RING;
	INIT_LIST_HEAD(&pring->txq);
	INIT_LIST_HEAD(&pring->txcmplq);
	INIT_LIST_HEAD(&pring->iocb_continueq);
	spin_lock_init(&pring->ring_lock);

	if (phba->cfg_nvme_io_channel) {
		pring = phba->sli4_hba.nvmels_wq->pring;
		pring->flag = 0;
		pring->ringno = LPFC_ELS_RING;
		INIT_LIST_HEAD(&pring->txq);
		INIT_LIST_HEAD(&pring->txcmplq);
		INIT_LIST_HEAD(&pring->iocb_continueq);
		spin_lock_init(&pring->ring_lock);
	}

	if (phba->cfg_fof) {
		pring = phba->sli4_hba.oas_wq->pring;
		pring->flag = 0;
		pring->ringno = LPFC_FCP_RING;
		INIT_LIST_HEAD(&pring->txq);
		INIT_LIST_HEAD(&pring->txcmplq);
		INIT_LIST_HEAD(&pring->iocb_continueq);
		spin_lock_init(&pring->ring_lock);
	}

	spin_unlock_irq(&phba->hbalock);
}