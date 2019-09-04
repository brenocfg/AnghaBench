#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct qla_hw_data {struct fw_blob* hablob; } ;
struct fw_blob {int /*<<< orphan*/ * fw; } ;
struct TYPE_7__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA82XX_FLASH_ROMIMAGE ; 
 int /*<<< orphan*/  QLA82XX_ROMUSB_GLB_SW_RESET ; 
 int /*<<< orphan*/  QLA82XX_UNIFIED_ROMIMAGE ; 
 int QLA_FUNCTION_FAILED ; 
 scalar_t__ QLA_SUCCESS ; 
 int ql2xfwloadbin ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_warn ; 
 struct fw_blob* qla2x00_request_firmware (TYPE_1__*) ; 
 scalar_t__ qla82xx_fw_load_from_blob (struct qla_hw_data*) ; 
 scalar_t__ qla82xx_fw_load_from_flash (struct qla_hw_data*) ; 
 scalar_t__ qla82xx_pinit_from_rom (TYPE_1__*) ; 
 int qla82xx_rd_32 (struct qla_hw_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ qla82xx_validate_firmware_blob (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
qla82xx_load_fw(scsi_qla_host_t *vha)
{
	int rst;
	struct fw_blob *blob;
	struct qla_hw_data *ha = vha->hw;

	if (qla82xx_pinit_from_rom(vha) != QLA_SUCCESS) {
		ql_log(ql_log_fatal, vha, 0x009f,
		    "Error during CRB initialization.\n");
		return QLA_FUNCTION_FAILED;
	}
	udelay(500);

	/* Bring QM and CAMRAM out of reset */
	rst = qla82xx_rd_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET);
	rst &= ~((1 << 28) | (1 << 24));
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET, rst);

	/*
	 * FW Load priority:
	 * 1) Operational firmware residing in flash.
	 * 2) Firmware via request-firmware interface (.bin file).
	 */
	if (ql2xfwloadbin == 2)
		goto try_blob_fw;

	ql_log(ql_log_info, vha, 0x00a0,
	    "Attempting to load firmware from flash.\n");

	if (qla82xx_fw_load_from_flash(ha) == QLA_SUCCESS) {
		ql_log(ql_log_info, vha, 0x00a1,
		    "Firmware loaded successfully from flash.\n");
		return QLA_SUCCESS;
	} else {
		ql_log(ql_log_warn, vha, 0x0108,
		    "Firmware load from flash failed.\n");
	}

try_blob_fw:
	ql_log(ql_log_info, vha, 0x00a2,
	    "Attempting to load firmware from blob.\n");

	/* Load firmware blob. */
	blob = ha->hablob = qla2x00_request_firmware(vha);
	if (!blob) {
		ql_log(ql_log_fatal, vha, 0x00a3,
		    "Firmware image not present.\n");
		goto fw_load_failed;
	}

	/* Validating firmware blob */
	if (qla82xx_validate_firmware_blob(vha,
		QLA82XX_FLASH_ROMIMAGE)) {
		/* Fallback to URI format */
		if (qla82xx_validate_firmware_blob(vha,
			QLA82XX_UNIFIED_ROMIMAGE)) {
			ql_log(ql_log_fatal, vha, 0x00a4,
			    "No valid firmware image found.\n");
			return QLA_FUNCTION_FAILED;
		}
	}

	if (qla82xx_fw_load_from_blob(ha) == QLA_SUCCESS) {
		ql_log(ql_log_info, vha, 0x00a5,
		    "Firmware loaded successfully from binary blob.\n");
		return QLA_SUCCESS;
	}

	ql_log(ql_log_fatal, vha, 0x00a6,
	       "Firmware load failed for binary blob.\n");
	blob->fw = NULL;
	blob = NULL;

fw_load_failed:
	return QLA_FUNCTION_FAILED;
}