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
struct TYPE_6__ {int isp82xx_no_md_cap; } ;
struct qla_hw_data {TYPE_1__ flags; int /*<<< orphan*/  allow_cna_fw_dump; } ;
struct TYPE_7__ {int /*<<< orphan*/  host; struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  qla2x00_wait_for_chip_reset (TYPE_2__*) ; 
 int /*<<< orphan*/  qla82xx_idc_lock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_idc_unlock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_set_reset_owner (TYPE_2__*) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_unblock_requests (int /*<<< orphan*/ ) ; 

void
qla82xx_fw_dump(scsi_qla_host_t *vha, int hardware_locked)
{
	struct qla_hw_data *ha = vha->hw;

	if (!ha->allow_cna_fw_dump)
		return;

	scsi_block_requests(vha->host);
	ha->flags.isp82xx_no_md_cap = 1;
	qla82xx_idc_lock(ha);
	qla82xx_set_reset_owner(vha);
	qla82xx_idc_unlock(ha);
	qla2x00_wait_for_chip_reset(vha);
	scsi_unblock_requests(vha->host);
}