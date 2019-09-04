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
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_WARNING ; 
 int __constant_cpu_to_le32 (int) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*) ; 
 scalar_t__ qla4_82xx_do_rom_fast_read (struct scsi_qla_host*,int,int*) ; 
 scalar_t__ qla4_82xx_rom_lock (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_82xx_rom_unlock (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static uint32_t *
qla4_82xx_read_flash_data(struct scsi_qla_host *ha, uint32_t *dwptr,
    uint32_t faddr, uint32_t length)
{
	uint32_t i;
	uint32_t val;
	int loops = 0;
	while ((qla4_82xx_rom_lock(ha) != 0) && (loops < 50000)) {
		udelay(100);
		cond_resched();
		loops++;
	}
	if (loops >= 50000) {
		ql4_printk(KERN_WARNING, ha, "ROM lock failed\n");
		return dwptr;
	}

	/* Dword reads to flash. */
	for (i = 0; i < length/4; i++, faddr += 4) {
		if (qla4_82xx_do_rom_fast_read(ha, faddr, &val)) {
			ql4_printk(KERN_WARNING, ha,
			    "Do ROM fast read failed\n");
			goto done_read;
		}
		dwptr[i] = __constant_cpu_to_le32(val);
	}

done_read:
	qla4_82xx_rom_unlock(ha);
	return dwptr;
}