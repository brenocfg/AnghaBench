#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_15__ {scalar_t__ nic_core_reset_owner; } ;
struct qla_hw_data {int portnum; TYPE_1__ flags; int /*<<< orphan*/  fcoe_reset_timeout; int /*<<< orphan*/  fcoe_dev_init_timeout; } ;
struct TYPE_16__ {struct qla_hw_data* hw; } ;
typedef  TYPE_2__ scsi_qla_host_t ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int /*<<< orphan*/  QLA83XX_IDC_DEV_STATE ; 
 int /*<<< orphan*/  QLA83XX_IDC_INITIALIZATION_TIMEOUT ; 
 int /*<<< orphan*/  QLA83XX_IDC_LOCK_RECOVERY ; 
 int /*<<< orphan*/  QLA83XX_IDC_MAJOR_VERSION ; 
 int /*<<< orphan*/  QLA83XX_IDC_MINOR_VERSION ; 
 int /*<<< orphan*/  QLA83XX_IDC_RESET_ACK_TIMEOUT ; 
 scalar_t__ QLA83XX_SUPP_IDC_MAJOR_VERSION ; 
 int QLA83XX_SUPP_IDC_MINOR_VERSION ; 
 scalar_t__ QLA8XXX_DEV_READY ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  __qla83xx_clear_drv_presence (TYPE_2__*) ; 
 int __qla83xx_set_drv_presence (TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,TYPE_2__*,int,char*) ; 
 int /*<<< orphan*/  ql_dbg_p3p ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_2__*,int,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla81xx_get_port_config (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla83xx_idc_lock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int qla83xx_idc_state_handler (TYPE_2__*) ; 
 int /*<<< orphan*/  qla83xx_idc_unlock (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla83xx_rd_reg (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  qla83xx_reset_ownership (TYPE_2__*) ; 
 int /*<<< orphan*/  qla83xx_wr_reg (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
qla83xx_nic_core_fw_load(scsi_qla_host_t *vha)
{
	int rval = QLA_SUCCESS;
	struct qla_hw_data *ha = vha->hw;
	uint32_t idc_major_ver, idc_minor_ver;
	uint16_t config[4];

	qla83xx_idc_lock(vha, 0);

	/* SV: TODO: Assign initialization timeout from
	 * flash-info / other param
	 */
	ha->fcoe_dev_init_timeout = QLA83XX_IDC_INITIALIZATION_TIMEOUT;
	ha->fcoe_reset_timeout = QLA83XX_IDC_RESET_ACK_TIMEOUT;

	/* Set our fcoe function presence */
	if (__qla83xx_set_drv_presence(vha) != QLA_SUCCESS) {
		ql_dbg(ql_dbg_p3p, vha, 0xb077,
		    "Error while setting DRV-Presence.\n");
		rval = QLA_FUNCTION_FAILED;
		goto exit;
	}

	/* Decide the reset ownership */
	qla83xx_reset_ownership(vha);

	/*
	 * On first protocol driver load:
	 * Init-Owner: Set IDC-Major-Version and Clear IDC-Lock-Recovery
	 * register.
	 * Others: Check compatibility with current IDC Major version.
	 */
	qla83xx_rd_reg(vha, QLA83XX_IDC_MAJOR_VERSION, &idc_major_ver);
	if (ha->flags.nic_core_reset_owner) {
		/* Set IDC Major version */
		idc_major_ver = QLA83XX_SUPP_IDC_MAJOR_VERSION;
		qla83xx_wr_reg(vha, QLA83XX_IDC_MAJOR_VERSION, idc_major_ver);

		/* Clearing IDC-Lock-Recovery register */
		qla83xx_wr_reg(vha, QLA83XX_IDC_LOCK_RECOVERY, 0);
	} else if (idc_major_ver != QLA83XX_SUPP_IDC_MAJOR_VERSION) {
		/*
		 * Clear further IDC participation if we are not compatible with
		 * the current IDC Major Version.
		 */
		ql_log(ql_log_warn, vha, 0xb07d,
		    "Failing load, idc_major_ver=%d, expected_major_ver=%d.\n",
		    idc_major_ver, QLA83XX_SUPP_IDC_MAJOR_VERSION);
		__qla83xx_clear_drv_presence(vha);
		rval = QLA_FUNCTION_FAILED;
		goto exit;
	}
	/* Each function sets its supported Minor version. */
	qla83xx_rd_reg(vha, QLA83XX_IDC_MINOR_VERSION, &idc_minor_ver);
	idc_minor_ver |= (QLA83XX_SUPP_IDC_MINOR_VERSION << (ha->portnum * 2));
	qla83xx_wr_reg(vha, QLA83XX_IDC_MINOR_VERSION, idc_minor_ver);

	if (ha->flags.nic_core_reset_owner) {
		memset(config, 0, sizeof(config));
		if (!qla81xx_get_port_config(vha, config))
			qla83xx_wr_reg(vha, QLA83XX_IDC_DEV_STATE,
			    QLA8XXX_DEV_READY);
	}

	rval = qla83xx_idc_state_handler(vha);

exit:
	qla83xx_idc_unlock(vha, 0);

	return rval;
}