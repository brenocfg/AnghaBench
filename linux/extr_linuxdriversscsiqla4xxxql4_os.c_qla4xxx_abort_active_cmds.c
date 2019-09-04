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
struct srb {int /*<<< orphan*/  srb_ref; TYPE_1__* cmd; } ;
struct scsi_qla_host {int /*<<< orphan*/  hardware_lock; TYPE_2__* host; } ;
struct TYPE_4__ {int can_queue; } ;
struct TYPE_3__ {int result; } ;

/* Variables and functions */
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct srb* qla4xxx_del_from_active_array (struct scsi_qla_host*,int) ; 
 int /*<<< orphan*/  qla4xxx_srb_compl ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qla4xxx_abort_active_cmds(struct scsi_qla_host *ha, int res)
{
	struct srb *srb;
	int i;
	unsigned long flags;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	for (i = 0; i < ha->host->can_queue; i++) {
		srb = qla4xxx_del_from_active_array(ha, i);
		if (srb != NULL) {
			srb->cmd->result = res;
			kref_put(&srb->srb_ref, qla4xxx_srb_compl);
		}
	}
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
}