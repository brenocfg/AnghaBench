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
typedef  scalar_t__ uint32_t ;
struct scsi_qla_host {int /*<<< orphan*/  hw_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRB_RCVPEG_STATE ; 
 int /*<<< orphan*/  DEBUG2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 scalar_t__ PHAN_PEG_RCV_INITIALIZED ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  ql4_printk (int /*<<< orphan*/ ,struct scsi_qla_host*,char*,scalar_t__) ; 
 scalar_t__ qla4_82xx_rd_32 (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int qla4_82xx_rcvpeg_ready(struct scsi_qla_host *ha)
{
	uint32_t state = 0;
	int loops = 0;

	/* Window 1 call */
	read_lock(&ha->hw_lock);
	state = qla4_82xx_rd_32(ha, CRB_RCVPEG_STATE);
	read_unlock(&ha->hw_lock);

	while ((state != PHAN_PEG_RCV_INITIALIZED) && (loops < 30000)) {
		udelay(100);
		/* Window 1 call */
		read_lock(&ha->hw_lock);
		state = qla4_82xx_rd_32(ha, CRB_RCVPEG_STATE);
		read_unlock(&ha->hw_lock);

		loops++;
	}

	if (loops >= 30000) {
		DEBUG2(ql4_printk(KERN_INFO, ha,
		    "Receive Peg initialization not complete: 0x%x.\n", state));
		return QLA_ERROR;
	}

	return QLA_SUCCESS;
}