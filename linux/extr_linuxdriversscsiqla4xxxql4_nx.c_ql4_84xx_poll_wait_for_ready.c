#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct scsi_qla_host {TYPE_1__* isp_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rd_reg_indirect ) (struct scsi_qla_host*,int,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  TIMEOUT_100_MS ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_qla_host*,int,int*) ; 
 scalar_t__ time_after_eq (unsigned long,unsigned long) ; 

__attribute__((used)) static uint32_t ql4_84xx_poll_wait_for_ready(struct scsi_qla_host *ha,
					     uint32_t addr1, uint32_t mask)
{
	unsigned long timeout;
	uint32_t rval = QLA_SUCCESS;
	uint32_t temp;

	timeout = jiffies + msecs_to_jiffies(TIMEOUT_100_MS);
	do {
		ha->isp_ops->rd_reg_indirect(ha, addr1, &temp);
		if ((temp & mask) != 0)
			break;

		if (time_after_eq(jiffies, timeout)) {
			ql4_printk(KERN_INFO, ha, "Error in processing rdmdio entry\n");
			return QLA_ERROR;
		}
	} while (1);

	return rval;
}