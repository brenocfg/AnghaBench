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
struct TYPE_5__ {scalar_t__ eqav; } ;
struct TYPE_6__ {TYPE_2__ pc_sli4_params; } ;
struct lpfc_hba {TYPE_3__ sli4_hba; } ;
struct lpfc_eqe {int dummy; } ;
struct TYPE_4__ {struct lpfc_eqe* eqe; } ;

/* Variables and functions */
 int bf_get_le32 (int /*<<< orphan*/ ,struct lpfc_eqe*) ; 
 int /*<<< orphan*/  lpfc_eqe_valid ; 
 int /*<<< orphan*/  mb () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct lpfc_eqe *
lpfc_sli4_eq_get(struct lpfc_queue *q)
{
	struct lpfc_hba *phba;
	struct lpfc_eqe *eqe;
	uint32_t idx;

	/* sanity check on queue memory */
	if (unlikely(!q))
		return NULL;
	phba = q->phba;
	eqe = q->qe[q->hba_index].eqe;

	/* If the next EQE is not valid then we are done */
	if (bf_get_le32(lpfc_eqe_valid, eqe) != q->qe_valid)
		return NULL;
	/* If the host has not yet processed the next entry then we are done */
	idx = ((q->hba_index + 1) % q->entry_count);
	if (idx == q->host_index)
		return NULL;

	q->hba_index = idx;
	/* if the index wrapped around, toggle the valid bit */
	if (phba->sli4_hba.pc_sli4_params.eqav && !q->hba_index)
		q->qe_valid = (q->qe_valid) ? 0 : 1;


	/*
	 * insert barrier for instruction interlock : data from the hardware
	 * must have the valid bit checked before it can be copied and acted
	 * upon. Speculative instructions were allowing a bcopy at the start
	 * of lpfc_sli4_fp_handle_wcqe(), which is called immediately
	 * after our return, to copy data before the valid bit check above
	 * was done. As such, some of the copied data was stale. The barrier
	 * ensures the check is before any data is copied.
	 */
	mb();
	return eqe;
}