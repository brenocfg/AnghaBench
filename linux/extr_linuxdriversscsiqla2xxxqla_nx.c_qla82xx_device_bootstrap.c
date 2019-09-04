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
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {scalar_t__ isp82xx_fw_hung; } ;
struct qla_hw_data {TYPE_1__ flags; } ;
struct TYPE_7__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA82XX_CRB_DEV_STATE ; 
 int /*<<< orphan*/  QLA82XX_PEG_ALIVE_COUNTER ; 
 int /*<<< orphan*/  QLA8XXX_DEV_FAILED ; 
 int /*<<< orphan*/  QLA8XXX_DEV_INITIALIZING ; 
 int /*<<< orphan*/  QLA8XXX_DEV_READY ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  qla82xx_clear_drv_active (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_idc_lock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_idc_unlock (struct qla_hw_data*) ; 
 int qla82xx_need_reset (struct qla_hw_data*) ; 
 scalar_t__ qla82xx_rd_32 (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla82xx_rom_lock_recovery (struct qla_hw_data*) ; 
 int qla82xx_start_firmware (TYPE_2__*) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla82xx_device_bootstrap(scsi_qla_host_t *vha)
{
	int rval = QLA_SUCCESS;
	int i;
	uint32_t old_count, count;
	struct qla_hw_data *ha = vha->hw;
	int need_reset = 0;

	need_reset = qla82xx_need_reset(ha);

	if (need_reset) {
		/* We are trying to perform a recovery here. */
		if (ha->flags.isp82xx_fw_hung)
			qla82xx_rom_lock_recovery(ha);
	} else  {
		old_count = qla82xx_rd_32(ha, QLA82XX_PEG_ALIVE_COUNTER);
		for (i = 0; i < 10; i++) {
			msleep(200);
			count = qla82xx_rd_32(ha, QLA82XX_PEG_ALIVE_COUNTER);
			if (count != old_count) {
				rval = QLA_SUCCESS;
				goto dev_ready;
			}
		}
		qla82xx_rom_lock_recovery(ha);
	}

	/* set to DEV_INITIALIZING */
	ql_log(ql_log_info, vha, 0x009e,
	    "HW State: INITIALIZING.\n");
	qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE, QLA8XXX_DEV_INITIALIZING);

	qla82xx_idc_unlock(ha);
	rval = qla82xx_start_firmware(vha);
	qla82xx_idc_lock(ha);

	if (rval != QLA_SUCCESS) {
		ql_log(ql_log_fatal, vha, 0x00ad,
		    "HW State: FAILED.\n");
		qla82xx_clear_drv_active(ha);
		qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE, QLA8XXX_DEV_FAILED);
		return rval;
	}

dev_ready:
	ql_log(ql_log_info, vha, 0x00ae,
	    "HW State: READY.\n");
	qla82xx_wr_32(ha, QLA82XX_CRB_DEV_STATE, QLA8XXX_DEV_READY);

	return QLA_SUCCESS;
}