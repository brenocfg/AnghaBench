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
typedef  int u64 ;
typedef  int u32 ;
struct qla_hw_data {int flt_region_bootload; int /*<<< orphan*/  hw_lock; } ;

/* Variables and functions */
 int BOOTLD_START ; 
 int IMAGE_START ; 
 scalar_t__ QLA82XX_CRB_PEG_NET_0 ; 
 scalar_t__ QLA82XX_ROMUSB_GLB_SW_RESET ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  qla82xx_pci_mem_write_2M (struct qla_hw_data*,long,int*,int) ; 
 scalar_t__ qla82xx_rom_fast_read (struct qla_hw_data*,long,int*) ; 
 int /*<<< orphan*/  qla82xx_wr_32 (struct qla_hw_data*,scalar_t__,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int
qla82xx_fw_load_from_flash(struct qla_hw_data *ha)
{
	int  i;
	long size = 0;
	long flashaddr = ha->flt_region_bootload << 2;
	long memaddr = BOOTLD_START;
	u64 data;
	u32 high, low;
	size = (IMAGE_START - BOOTLD_START) / 8;

	for (i = 0; i < size; i++) {
		if ((qla82xx_rom_fast_read(ha, flashaddr, (int *)&low)) ||
		    (qla82xx_rom_fast_read(ha, flashaddr + 4, (int *)&high))) {
			return -1;
		}
		data = ((u64)high << 32) | low ;
		qla82xx_pci_mem_write_2M(ha, memaddr, &data, 8);
		flashaddr += 8;
		memaddr += 8;

		if (i % 0x1000 == 0)
			msleep(1);
	}
	udelay(100);
	read_lock(&ha->hw_lock);
	qla82xx_wr_32(ha, QLA82XX_CRB_PEG_NET_0 + 0x18, 0x1020);
	qla82xx_wr_32(ha, QLA82XX_ROMUSB_GLB_SW_RESET, 0x80001e);
	read_unlock(&ha->hw_lock);
	return 0;
}