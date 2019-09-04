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
struct scsi_qla_host {int func_num; int request_in; int /*<<< orphan*/  nx_db_wr_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  qla4_82xx_wr_32 (struct scsi_qla_host*,int /*<<< orphan*/ ,int) ; 

void qla4_82xx_queue_iocb(struct scsi_qla_host *ha)
{
	uint32_t dbval = 0;

	dbval = 0x14 | (ha->func_num << 5);
	dbval = dbval | (0 << 8) | (ha->request_in << 16);

	qla4_82xx_wr_32(ha, ha->nx_db_wr_ptr, ha->request_in);
}