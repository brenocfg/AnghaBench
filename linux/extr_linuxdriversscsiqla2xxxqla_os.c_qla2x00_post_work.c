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
struct scsi_qla_host {int /*<<< orphan*/  iocb_work; TYPE_1__* hw; int /*<<< orphan*/  work_lock; int /*<<< orphan*/  dpc_flags; int /*<<< orphan*/  work_list; } ;
struct qla_work_evt {int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOCB_WORK_ACTIVE ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
qla2x00_post_work(struct scsi_qla_host *vha, struct qla_work_evt *e)
{
	unsigned long flags;
	bool q = false;

	spin_lock_irqsave(&vha->work_lock, flags);
	list_add_tail(&e->list, &vha->work_list);

	if (!test_and_set_bit(IOCB_WORK_ACTIVE, &vha->dpc_flags))
		q = true;

	spin_unlock_irqrestore(&vha->work_lock, flags);

	if (q)
		queue_work(vha->hw->wq, &vha->iocb_work);

	return QLA_SUCCESS;
}