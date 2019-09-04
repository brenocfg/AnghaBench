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

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  QLA82XX_ROMUSB_ROM_ABYTE_CNT ; 
 int /*<<< orphan*/  QLA82XX_ROMUSB_ROM_ADDRESS ; 
 int /*<<< orphan*/  QLA82XX_ROMUSB_ROM_DUMMY_BYTE_CNT ; 
 int /*<<< orphan*/  QLA82XX_ROMUSB_ROM_INSTR_OPCODE ; 
 int /*<<< orphan*/  QLA82XX_ROMUSB_ROM_RDATA ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int qla4_82xx_rd_32 (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 scalar_t__ qla4_82xx_wait_rom_done (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_82xx_wr_32 (struct scsi_qla_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
qla4_82xx_do_rom_fast_read(struct scsi_qla_host *ha, int addr, int *valp)
{
	qla4_82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_ADDRESS, addr);
	qla4_82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_DUMMY_BYTE_CNT, 0);
	qla4_82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_ABYTE_CNT, 3);
	qla4_82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_INSTR_OPCODE, 0xb);
	if (qla4_82xx_wait_rom_done(ha)) {
		printk("%s: Error waiting for rom done\n", DRIVER_NAME);
		return -1;
	}
	/* reset abyte_cnt and dummy_byte_cnt */
	qla4_82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_DUMMY_BYTE_CNT, 0);
	udelay(10);
	qla4_82xx_wr_32(ha, QLA82XX_ROMUSB_ROM_ABYTE_CNT, 0);

	*valp = qla4_82xx_rd_32(ha, QLA82XX_ROMUSB_ROM_RDATA);
	return 0;
}