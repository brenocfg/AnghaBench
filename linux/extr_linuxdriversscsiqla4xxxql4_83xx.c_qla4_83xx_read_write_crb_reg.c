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
typedef  int /*<<< orphan*/  uint32_t ;
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qla4_83xx_rd_reg_indirect (struct scsi_qla_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla4_83xx_wr_reg_indirect (struct scsi_qla_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qla4_83xx_read_write_crb_reg(struct scsi_qla_host *ha,
					 uint32_t raddr, uint32_t waddr)
{
	uint32_t value;

	qla4_83xx_rd_reg_indirect(ha, raddr, &value);
	qla4_83xx_wr_reg_indirect(ha, waddr, value);
}