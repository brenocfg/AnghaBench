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
typedef  int uint32_t ;
struct lpfc_queue {size_t hba_index; int qe_valid; int entry_count; int host_index; TYPE_1__* qe; struct lpfc_hba* phba; } ;
struct TYPE_5__ {scalar_t__ cqav; } ;
struct TYPE_6__ {TYPE_2__ pc_sli4_params; } ;
struct lpfc_hba {TYPE_3__ sli4_hba; } ;
struct lpfc_cqe {int dummy; } ;
struct TYPE_4__ {struct lpfc_cqe* cqe; } ;

/* Variables and functions */
 int bf_get_le32 (int /*<<< orphan*/ ,struct lpfc_cqe*) ; 
 int /*<<< orphan*/  lpfc_cqe_valid ; 
 int /*<<< orphan*/  mb () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct lpfc_cqe *
lpfc_sli4_cq_get(struct lpfc_queue *q)
{
	struct lpfc_hba *phba;
	struct lpfc_cqe *cqe;
	uint32_t idx;

	/* sanity check on queue memory */
	if (unlikely(!q))
		return NULL;
	phba = q->phba;
	cqe = q->qe[q->hba_index].cqe;

	/* If the next CQE is not valid then we are done */
	if (bf_get_le32(lpfc_cqe_valid, cqe) != q->qe_valid)
		return NULL;
	/* If the host has not yet processed the next entry then we are done */
	idx = ((q->hba_index + 1) % q->entry_count);
	if (idx == q->host_index)
		return NULL;

	q->hba_index = idx;
	/* if the index wrapped around, toggle the valid bit */
	if (phba->sli4_hba.pc_sli4_params.cqav && !q->hba_index)
		q->qe_valid = (q->qe_valid) ? 0 : 1;

	/*
	 * insert barrier for instruction interlock : data from the hardware
	 * must have the valid bit checked before it can be copied and acted
	 * upon. Given what was seen in lpfc_sli4_cq_get() of speculative
	 * instructions allowing action on content before valid bit checked,
	 * add barrier here as well. May not be needed as "content" is a
	 * single 32-bit entity here (vs multi word structure for cq's).
	 */
	mb();
	return cqe;
}