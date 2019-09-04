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
typedef  size_t uint32_t ;
typedef  scalar_t__ uint16_t ;
struct lpfc_queue {scalar_t__ queue_id; int /*<<< orphan*/  irqwork; int /*<<< orphan*/  assoc_qp; } ;
struct TYPE_2__ {scalar_t__* nvme_cq_map; scalar_t__* fcp_cq_map; int /*<<< orphan*/ * hba_eq; struct lpfc_queue* nvmels_cq; struct lpfc_queue** fcp_cq; struct lpfc_queue** nvme_cq; struct lpfc_queue** nvmet_cqset; } ;
struct lpfc_hba {scalar_t__ cfg_nvmet_mrq; int /*<<< orphan*/  wq; TYPE_1__ sli4_hba; } ;
struct lpfc_eqe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_SLI ; 
 scalar_t__ bf_get_le32 (int /*<<< orphan*/ ,struct lpfc_eqe*) ; 
 int /*<<< orphan*/  lpfc_eqe_major_code ; 
 int /*<<< orphan*/  lpfc_eqe_minor_code ; 
 int /*<<< orphan*/  lpfc_eqe_resource_id ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,...) ; 
 int /*<<< orphan*/  lpfc_sli4_sp_handle_eqe (struct lpfc_hba*,struct lpfc_eqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
lpfc_sli4_hba_handle_eqe(struct lpfc_hba *phba, struct lpfc_eqe *eqe,
			uint32_t qidx)
{
	struct lpfc_queue *cq = NULL;
	uint16_t cqid, id;

	if (unlikely(bf_get_le32(lpfc_eqe_major_code, eqe) != 0)) {
		lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
				"0366 Not a valid completion "
				"event: majorcode=x%x, minorcode=x%x\n",
				bf_get_le32(lpfc_eqe_major_code, eqe),
				bf_get_le32(lpfc_eqe_minor_code, eqe));
		return;
	}

	/* Get the reference to the corresponding CQ */
	cqid = bf_get_le32(lpfc_eqe_resource_id, eqe);

	if (phba->cfg_nvmet_mrq && phba->sli4_hba.nvmet_cqset) {
		id = phba->sli4_hba.nvmet_cqset[0]->queue_id;
		if ((cqid >= id) && (cqid < (id + phba->cfg_nvmet_mrq))) {
			/* Process NVMET unsol rcv */
			cq = phba->sli4_hba.nvmet_cqset[cqid - id];
			goto  process_cq;
		}
	}

	if (phba->sli4_hba.nvme_cq_map &&
	    (cqid == phba->sli4_hba.nvme_cq_map[qidx])) {
		/* Process NVME / NVMET command completion */
		cq = phba->sli4_hba.nvme_cq[qidx];
		goto  process_cq;
	}

	if (phba->sli4_hba.fcp_cq_map &&
	    (cqid == phba->sli4_hba.fcp_cq_map[qidx])) {
		/* Process FCP command completion */
		cq = phba->sli4_hba.fcp_cq[qidx];
		goto  process_cq;
	}

	if (phba->sli4_hba.nvmels_cq &&
	    (cqid == phba->sli4_hba.nvmels_cq->queue_id)) {
		/* Process NVME unsol rcv */
		cq = phba->sli4_hba.nvmels_cq;
	}

	/* Otherwise this is a Slow path event */
	if (cq == NULL) {
		lpfc_sli4_sp_handle_eqe(phba, eqe, phba->sli4_hba.hba_eq[qidx]);
		return;
	}

process_cq:
	if (unlikely(cqid != cq->queue_id)) {
		lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
				"0368 Miss-matched fast-path completion "
				"queue identifier: eqcqid=%d, fcpcqid=%d\n",
				cqid, cq->queue_id);
		return;
	}

	/* Save EQ associated with this CQ */
	cq->assoc_qp = phba->sli4_hba.hba_eq[qidx];

	if (!queue_work(phba->wq, &cq->irqwork))
		lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
				"0363 Cannot schedule soft IRQ "
				"for CQ eqcqid=%d, cqid=%d on CPU %d\n",
				cqid, cq->queue_id, smp_processor_id());
}