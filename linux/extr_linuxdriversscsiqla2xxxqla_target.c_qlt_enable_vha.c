#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct qla_tgt* qla_tgt; } ;
struct scsi_qla_host {scalar_t__ vp_idx; TYPE_1__ vha_tgt; struct qla_hw_data* hw; } ;
struct qla_tgt {scalar_t__ tgt_stopped; } ;
struct qla_hw_data {int /*<<< orphan*/  hardware_lock; int /*<<< orphan*/  pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dpc_flags; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_ABORT_NEEDED ; 
 int /*<<< orphan*/  dump_stack () ; 
 TYPE_2__* pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*) ; 
 int /*<<< orphan*/  ql_dbg_tgt ; 
 int /*<<< orphan*/  qla24xx_disable_vp (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla24xx_enable_vp (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla2x00_wait_for_hba_online (TYPE_2__*) ; 
 int /*<<< orphan*/  qla2xxx_wake_dpc (TYPE_2__*) ; 
 int /*<<< orphan*/  qlt_set_mode (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void
qlt_enable_vha(struct scsi_qla_host *vha)
{
	struct qla_hw_data *ha = vha->hw;
	struct qla_tgt *tgt = vha->vha_tgt.qla_tgt;
	unsigned long flags;
	scsi_qla_host_t *base_vha = pci_get_drvdata(ha->pdev);

	if (!tgt) {
		ql_dbg(ql_dbg_tgt, vha, 0xe069,
		    "Unable to locate qla_tgt pointer from"
		    " struct qla_hw_data\n");
		dump_stack();
		return;
	}

	spin_lock_irqsave(&ha->hardware_lock, flags);
	tgt->tgt_stopped = 0;
	qlt_set_mode(vha);
	spin_unlock_irqrestore(&ha->hardware_lock, flags);

	if (vha->vp_idx) {
		qla24xx_disable_vp(vha);
		qla24xx_enable_vp(vha);
	} else {
		set_bit(ISP_ABORT_NEEDED, &base_vha->dpc_flags);
		qla2xxx_wake_dpc(base_vha);
		qla2x00_wait_for_hba_online(base_vha);
	}
}