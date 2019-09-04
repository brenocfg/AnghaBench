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
struct be_queue_info {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {struct be_queue_info cq; } ;
struct TYPE_4__ {TYPE_1__ mcc_obj; } ;
struct beiscsi_hba {TYPE_2__ ctrl; } ;
struct be_mcc_compl {int flags; } ;

/* Variables and functions */
 int CQE_FLAGS_ASYNC_MASK ; 
 int CQE_FLAGS_COMPLETED_MASK ; 
 int CQE_FLAGS_VALID_MASK ; 
 scalar_t__ beiscsi_hba_in_error (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_process_async_event (struct beiscsi_hba*,struct be_mcc_compl*) ; 
 int /*<<< orphan*/  beiscsi_process_mcc_compl (TYPE_2__*,struct be_mcc_compl*) ; 
 int /*<<< orphan*/  hwi_ring_cq_db (struct beiscsi_hba*,int /*<<< orphan*/ ,unsigned int,int) ; 
 void* le32_to_cpu (int) ; 
 int /*<<< orphan*/  queue_tail_inc (struct be_queue_info*) ; 
 struct be_mcc_compl* queue_tail_node (struct be_queue_info*) ; 

void beiscsi_process_mcc_cq(struct beiscsi_hba *phba)
{
	struct be_queue_info *mcc_cq;
	struct  be_mcc_compl *mcc_compl;
	unsigned int num_processed = 0;

	mcc_cq = &phba->ctrl.mcc_obj.cq;
	mcc_compl = queue_tail_node(mcc_cq);
	mcc_compl->flags = le32_to_cpu(mcc_compl->flags);
	while (mcc_compl->flags & CQE_FLAGS_VALID_MASK) {
		if (beiscsi_hba_in_error(phba))
			return;

		if (num_processed >= 32) {
			hwi_ring_cq_db(phba, mcc_cq->id,
					num_processed, 0);
			num_processed = 0;
		}
		if (mcc_compl->flags & CQE_FLAGS_ASYNC_MASK) {
			beiscsi_process_async_event(phba, mcc_compl);
		} else if (mcc_compl->flags & CQE_FLAGS_COMPLETED_MASK) {
			beiscsi_process_mcc_compl(&phba->ctrl, mcc_compl);
		}

		mcc_compl->flags = 0;
		queue_tail_inc(mcc_cq);
		mcc_compl = queue_tail_node(mcc_cq);
		mcc_compl->flags = le32_to_cpu(mcc_compl->flags);
		num_processed++;
	}

	if (num_processed > 0)
		hwi_ring_cq_db(phba, mcc_cq->id, num_processed, 1);
}