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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA83XX_IDC_DEV_STATE ; 
 int /*<<< orphan*/  QLA83XX_IDC_GRACEFUL_RESET ; 
 int /*<<< orphan*/  QLA8XXX_DEV_FAILED ; 
 int /*<<< orphan*/  QLA8XXX_DEV_INITIALIZING ; 
 int /*<<< orphan*/  QLA8XXX_DEV_READY ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  __qla83xx_get_idc_control (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __qla83xx_set_idc_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ql_dbg_p3p ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  qla83xx_idc_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla83xx_idc_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qla83xx_restart_nic_firmware (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla83xx_wr_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla83xx_device_bootstrap(scsi_qla_host_t *vha)
{
	int rval = QLA_SUCCESS;
	uint32_t idc_control;

	qla83xx_wr_reg(vha, QLA83XX_IDC_DEV_STATE, QLA8XXX_DEV_INITIALIZING);
	ql_log(ql_log_info, vha, 0xb069, "HW State: INITIALIZING.\n");

	/* Clearing IDC-Control Graceful-Reset Bit before resetting f/w */
	__qla83xx_get_idc_control(vha, &idc_control);
	idc_control &= ~QLA83XX_IDC_GRACEFUL_RESET;
	__qla83xx_set_idc_control(vha, 0);

	qla83xx_idc_unlock(vha, 0);
	rval = qla83xx_restart_nic_firmware(vha);
	qla83xx_idc_lock(vha, 0);

	if (rval != QLA_SUCCESS) {
		ql_log(ql_log_fatal, vha, 0xb06a,
		    "Failed to restart NIC f/w.\n");
		qla83xx_wr_reg(vha, QLA83XX_IDC_DEV_STATE, QLA8XXX_DEV_FAILED);
		ql_log(ql_log_info, vha, 0xb06b, "HW State: FAILED.\n");
	} else {
		ql_dbg(ql_dbg_p3p, vha, 0xb06c,
		    "Success in restarting nic f/w.\n");
		qla83xx_wr_reg(vha, QLA83XX_IDC_DEV_STATE, QLA8XXX_DEV_READY);
		ql_log(ql_log_info, vha, 0xb06d, "HW State: READY.\n");
	}

	return rval;
}