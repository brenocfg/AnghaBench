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
struct scsi_qla_host {int dummy; } ;
struct qla_qpair {int /*<<< orphan*/  qp_lock; int /*<<< orphan*/  rsp; } ;
struct nvme_fc_local_port {struct scsi_qla_host* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  qla24xx_process_response_queue (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void qla_nvme_poll(struct nvme_fc_local_port *lport, void *hw_queue_handle)
{
	struct qla_qpair *qpair = hw_queue_handle;
	unsigned long flags;
	struct scsi_qla_host *vha = lport->private;

	spin_lock_irqsave(&qpair->qp_lock, flags);
	qla24xx_process_response_queue(vha, qpair->rsp);
	spin_unlock_irqrestore(&qpair->qp_lock, flags);
}