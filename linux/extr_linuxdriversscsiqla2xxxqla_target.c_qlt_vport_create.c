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
struct TYPE_3__ {int /*<<< orphan*/  tgt_host_action_mutex; int /*<<< orphan*/  tgt_mutex; int /*<<< orphan*/ * qla_tgt; } ;
struct scsi_qla_host {TYPE_1__ vha_tgt; } ;
struct TYPE_4__ {int /*<<< orphan*/  atio_q_length; } ;
struct qla_hw_data {TYPE_2__ tgt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATIO_ENTRY_CNT_24XX ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qlt_add_target (struct qla_hw_data*,struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qlt_clear_mode (struct scsi_qla_host*) ; 

void
qlt_vport_create(struct scsi_qla_host *vha, struct qla_hw_data *ha)
{
	vha->vha_tgt.qla_tgt = NULL;

	mutex_init(&vha->vha_tgt.tgt_mutex);
	mutex_init(&vha->vha_tgt.tgt_host_action_mutex);

	qlt_clear_mode(vha);

	/*
	 * NOTE: Currently the value is kept the same for <24xx and
	 * >=24xx ISPs. If it is necessary to change it,
	 * the check should be added for specific ISPs,
	 * assigning the value appropriately.
	 */
	ha->tgt.atio_q_length = ATIO_ENTRY_CNT_24XX;

	qlt_add_target(ha, vha);
}