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
struct lpfc_register {scalar_t__ word0; } ;
struct lpfc_queue {size_t hba_index; size_t host_index; int entry_count; int queue_id; struct lpfc_hba* phba; TYPE_2__* qe; } ;
struct TYPE_4__ {int /*<<< orphan*/  cqav; } ;
struct TYPE_6__ {int /*<<< orphan*/  CQDBregaddr; TYPE_1__ pc_sli4_params; } ;
struct lpfc_hba {TYPE_3__ sli4_hba; } ;
struct lpfc_cqe {int dummy; } ;
struct TYPE_5__ {struct lpfc_cqe* cqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  bf_set (int /*<<< orphan*/ ,struct lpfc_register*,int) ; 
 int /*<<< orphan*/  bf_set_le32 (int /*<<< orphan*/ ,struct lpfc_cqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_cqe_valid ; 
 int /*<<< orphan*/  lpfc_if6_cq_doorbell_arm ; 
 int /*<<< orphan*/  lpfc_if6_cq_doorbell_cqid ; 
 int /*<<< orphan*/  lpfc_if6_cq_doorbell_num_released ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (scalar_t__,int /*<<< orphan*/ ) ; 

uint32_t
lpfc_sli4_if6_cq_release(struct lpfc_queue *q, bool arm)
{
	uint32_t released = 0;
	struct lpfc_hba *phba;
	struct lpfc_cqe *temp_qe;
	struct lpfc_register doorbell;

	/* sanity check on queue memory */
	if (unlikely(!q))
		return 0;
	phba = q->phba;

	/* while there are valid entries */
	while (q->hba_index != q->host_index) {
		if (!phba->sli4_hba.pc_sli4_params.cqav) {
			temp_qe = q->qe[q->host_index].cqe;
			bf_set_le32(lpfc_cqe_valid, temp_qe, 0);
		}
		released++;
		q->host_index = ((q->host_index + 1) % q->entry_count);
	}
	if (unlikely(released == 0 && !arm))
		return 0;

	/* ring doorbell for number popped */
	doorbell.word0 = 0;
	if (arm)
		bf_set(lpfc_if6_cq_doorbell_arm, &doorbell, 1);
	bf_set(lpfc_if6_cq_doorbell_num_released, &doorbell, released);
	bf_set(lpfc_if6_cq_doorbell_cqid, &doorbell, q->queue_id);
	writel(doorbell.word0, q->phba->sli4_hba.CQDBregaddr);
	return released;
}