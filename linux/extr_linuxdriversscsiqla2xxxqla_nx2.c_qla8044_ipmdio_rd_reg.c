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
 int qla8044_poll_wait_for_ready (struct scsi_qla_host*,int,int) ; 
 int /*<<< orphan*/  qla8044_rd_reg_indirect (struct scsi_qla_host*,int,int*) ; 
 int /*<<< orphan*/  qla8044_wr_reg_indirect (struct scsi_qla_host*,int,int) ; 

__attribute__((used)) static uint32_t
qla8044_ipmdio_rd_reg(struct scsi_qla_host *vha,
	uint32_t addr1, uint32_t addr3, uint32_t mask, uint32_t addr)
{
	uint32_t temp;
	int ret = 0;

	ret = qla8044_poll_wait_for_ready(vha, addr1, mask);
	if (ret == -1)
		return -1;

	temp = (0x40000000 | addr);
	qla8044_wr_reg_indirect(vha, addr1, temp);

	ret = qla8044_poll_wait_for_ready(vha, addr1, mask);
	if (ret == -1)
		return 0;

	qla8044_rd_reg_indirect(vha, addr3, &ret);

	return ret;
}