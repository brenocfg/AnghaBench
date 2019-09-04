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
typedef  int u32 ;
struct scsi_qla_host {int /*<<< orphan*/  host_no; int /*<<< orphan*/  hardware_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isp_semaphore (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int,int,int) ; 
 int readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

int ql4xxx_sem_lock(struct scsi_qla_host * ha, u32 sem_mask, u32 sem_bits)
{
	uint32_t value;
	unsigned long flags;

	spin_lock_irqsave(&ha->hardware_lock, flags);
	writel((sem_mask | sem_bits), isp_semaphore(ha));
	value = readw(isp_semaphore(ha));
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
	if ((value & (sem_mask >> 16)) == sem_bits) {
		DEBUG2(printk("scsi%ld : Got SEM LOCK - mask= 0x%x, code = "
			      "0x%x, sema code=0x%x\n", ha->host_no,
			      sem_mask, sem_bits, value));
		return 1;
	}
	return 0;
}