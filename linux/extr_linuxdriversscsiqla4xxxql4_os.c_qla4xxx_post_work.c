#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct scsi_qla_host {int /*<<< orphan*/  work_lock; int /*<<< orphan*/  work_list; } ;
struct qla4_work_evt {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla4xxx_wake_dpc (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qla4xxx_post_work(struct scsi_qla_host *ha,
			     struct qla4_work_evt *e)
{
	unsigned long flags;

	spin_lock_irqsave(&ha->work_lock, flags);
	list_add_tail(&e->list, &ha->work_list);
	spin_unlock_irqrestore(&ha->work_lock, flags);
	qla4xxx_wake_dpc(ha);
}