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
struct scsi_qla_host {TYPE_3__* hw; } ;
struct qla_tgt_cmd {scalar_t__ sg_mapped; int /*<<< orphan*/  aborted; struct scsi_qla_host* vha; } ;
struct qla_qpair {int /*<<< orphan*/  qp_lock_ptr; struct scsi_qla_host* vha; } ;
struct atio_from_isp {int dummy; } ;
struct TYPE_5__ {TYPE_1__* tgt_ops; } ;
struct TYPE_6__ {TYPE_2__ tgt; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* free_cmd ) (struct qla_tgt_cmd*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int __qlt_send_term_exchange (struct qla_qpair*,struct qla_tgt_cmd*,struct atio_from_isp*) ; 
 int /*<<< orphan*/  qlt_alloc_qfull_cmd (struct scsi_qla_host*,struct atio_from_isp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qlt_unmap_sg (struct scsi_qla_host*,struct qla_tgt_cmd*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct qla_tgt_cmd*) ; 

__attribute__((used)) static void qlt_send_term_exchange(struct qla_qpair *qpair,
	struct qla_tgt_cmd *cmd, struct atio_from_isp *atio, int ha_locked,
	int ul_abort)
{
	struct scsi_qla_host *vha;
	unsigned long flags = 0;
	int rc;

	/* why use different vha? NPIV */
	if (cmd)
		vha = cmd->vha;
	else
		vha = qpair->vha;

	if (ha_locked) {
		rc = __qlt_send_term_exchange(qpair, cmd, atio);
		if (rc == -ENOMEM)
			qlt_alloc_qfull_cmd(vha, atio, 0, 0);
		goto done;
	}
	spin_lock_irqsave(qpair->qp_lock_ptr, flags);
	rc = __qlt_send_term_exchange(qpair, cmd, atio);
	if (rc == -ENOMEM)
		qlt_alloc_qfull_cmd(vha, atio, 0, 0);

done:
	if (cmd && !ul_abort && !cmd->aborted) {
		if (cmd->sg_mapped)
			qlt_unmap_sg(vha, cmd);
		vha->hw->tgt.tgt_ops->free_cmd(cmd);
	}

	if (!ha_locked)
		spin_unlock_irqrestore(qpair->qp_lock_ptr, flags);

	return;
}