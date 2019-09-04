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
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_qla_host {TYPE_1__* isp_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* wr_reg_indirect ) (struct scsi_qla_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int QLA_SUCCESS ; 
 int ql4_84xx_poll_wait_for_ready (struct scsi_qla_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct scsi_qla_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct scsi_qla_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ql4_84xx_ipmdio_wr_reg(struct scsi_qla_host *ha,
				  uint32_t addr1, uint32_t addr3,
				  uint32_t mask, uint32_t addr,
				  uint32_t value)
{
	int rval = QLA_SUCCESS;

	rval = ql4_84xx_poll_wait_for_ready(ha, addr1, mask);
	if (rval)
		goto exit_ipmdio_wr_reg;

	ha->isp_ops->wr_reg_indirect(ha, addr3, value);
	ha->isp_ops->wr_reg_indirect(ha, addr1, addr);

	rval = ql4_84xx_poll_wait_for_ready(ha, addr1, mask);
	if (rval)
		goto exit_ipmdio_wr_reg;

exit_ipmdio_wr_reg:
	return rval;
}