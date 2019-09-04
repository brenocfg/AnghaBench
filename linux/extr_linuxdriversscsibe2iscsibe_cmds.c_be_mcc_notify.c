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
typedef  int u32 ;
struct be_queue_info {int id; } ;
struct TYPE_4__ {struct be_queue_info q; } ;
struct TYPE_6__ {TYPE_2__* ptag_state; TYPE_1__ mcc_obj; } ;
struct beiscsi_hba {scalar_t__ db_va; TYPE_3__ ctrl; } ;
struct TYPE_5__ {int /*<<< orphan*/  tag_state; } ;

/* Variables and functions */
 int DB_MCCQ_NUM_POSTED_SHIFT ; 
 scalar_t__ DB_MCCQ_OFFSET ; 
 int DB_MCCQ_RING_ID_MASK ; 
 int /*<<< orphan*/  MCC_TAG_STATE_RUNNING ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

void be_mcc_notify(struct beiscsi_hba *phba, unsigned int tag)
{
	struct be_queue_info *mccq = &phba->ctrl.mcc_obj.q;
	u32 val = 0;

	set_bit(MCC_TAG_STATE_RUNNING, &phba->ctrl.ptag_state[tag].tag_state);
	val |= mccq->id & DB_MCCQ_RING_ID_MASK;
	val |= 1 << DB_MCCQ_NUM_POSTED_SHIFT;
	/* make request available for DMA */
	wmb();
	iowrite32(val, phba->db_va + DB_MCCQ_OFFSET);
}