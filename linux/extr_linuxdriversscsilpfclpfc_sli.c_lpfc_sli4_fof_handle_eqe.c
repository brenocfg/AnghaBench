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
typedef  scalar_t__ uint16_t ;
struct lpfc_queue {scalar_t__ queue_id; int /*<<< orphan*/  irqwork; int /*<<< orphan*/  assoc_qp; } ;
struct TYPE_4__ {int /*<<< orphan*/  fof_eq; struct lpfc_queue* oas_cq; } ;
struct TYPE_3__ {int sli_flag; } ;
struct lpfc_hba {int /*<<< orphan*/  wq; TYPE_2__ sli4_hba; TYPE_1__ sli; } ;
struct lpfc_eqe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_SLI ; 
 int LPFC_SLI_ACTIVE ; 
 scalar_t__ bf_get_le32 (int /*<<< orphan*/ ,struct lpfc_eqe*) ; 
 int /*<<< orphan*/  lpfc_eqe_major_code ; 
 int /*<<< orphan*/  lpfc_eqe_minor_code ; 
 int /*<<< orphan*/  lpfc_eqe_resource_id ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
lpfc_sli4_fof_handle_eqe(struct lpfc_hba *phba, struct lpfc_eqe *eqe)
{
	struct lpfc_queue *cq;
	uint16_t cqid;

	if (unlikely(bf_get_le32(lpfc_eqe_major_code, eqe) != 0)) {
		lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
				"9147 Not a valid completion "
				"event: majorcode=x%x, minorcode=x%x\n",
				bf_get_le32(lpfc_eqe_major_code, eqe),
				bf_get_le32(lpfc_eqe_minor_code, eqe));
		return;
	}

	/* Get the reference to the corresponding CQ */
	cqid = bf_get_le32(lpfc_eqe_resource_id, eqe);

	/* Next check for OAS */
	cq = phba->sli4_hba.oas_cq;
	if (unlikely(!cq)) {
		if (phba->sli.sli_flag & LPFC_SLI_ACTIVE)
			lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
					"9148 OAS completion queue "
					"does not exist\n");
		return;
	}

	if (unlikely(cqid != cq->queue_id)) {
		lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
				"9149 Miss-matched fast-path compl "
				"queue id: eqcqid=%d, fcpcqid=%d\n",
				cqid, cq->queue_id);
		return;
	}

	/* Save EQ associated with this CQ */
	cq->assoc_qp = phba->sli4_hba.fof_eq;

	/* CQ work will be processed on CPU affinitized to this IRQ */
	if (!queue_work(phba->wq, &cq->irqwork))
		lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
				"0367 Cannot schedule soft IRQ "
				"for CQ eqcqid=%d, cqid=%d on CPU %d\n",
				cqid, cq->queue_id, smp_processor_id());
}