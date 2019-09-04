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
typedef  int uint32_t ;
struct qla_hw_data {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA82XX_ROMUSB_ROM_INSTR_OPCODE ; 
 int /*<<< orphan*/  QLA82XX_ROMUSB_ROM_WDATA ; 
 int /*<<< orphan*/ * pci_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 scalar_t__ qla82xx_flash_set_write_enable (struct qla_hw_data*) ; 
 int qla82xx_flash_wait_write_finish (struct qla_hw_data*) ; 
 scalar_t__ qla82xx_wait_rom_done (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
qla82xx_write_status_reg(struct qla_hw_data *ha, uint32_t val)
{
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);
	if (qla82xx_flash_set_write_enable(ha))
		return -1;
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_WDATA, val);
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_INSTR_OPCODE, 0x1);
	if (qla82xx_wait_rom_done(ha)) {
		ql_log(ql_log_warn, vha, 0xb00e,
		    "Error waiting for rom done.\n");
		return -1;
	}
	return qla82xx_flash_wait_write_finish(ha);
}