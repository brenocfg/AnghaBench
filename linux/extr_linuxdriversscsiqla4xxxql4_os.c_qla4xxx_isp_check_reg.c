#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct scsi_qla_host {TYPE_2__* reg; TYPE_1__* qla4_82xx_reg; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl_status; } ;
struct TYPE_3__ {int /*<<< orphan*/  host_status; } ;

/* Variables and functions */
 scalar_t__ QL4_ISP_REG_DISCONNECT ; 
 int /*<<< orphan*/  QLA8XXX_PEG_ALIVE_COUNTER ; 
 int QLA_ERROR ; 
 int QLA_SUCCESS ; 
 scalar_t__ is_qla8022 (struct scsi_qla_host*) ; 
 scalar_t__ is_qla8032 (struct scsi_qla_host*) ; 
 scalar_t__ is_qla8042 (struct scsi_qla_host*) ; 
 scalar_t__ qla4_8xxx_rd_direct (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 scalar_t__ readl (int /*<<< orphan*/ *) ; 
 scalar_t__ readw (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qla4xxx_isp_check_reg(struct scsi_qla_host *ha)
{
	u32 reg_val = 0;
	int rval = QLA_SUCCESS;

	if (is_qla8022(ha))
		reg_val = readl(&ha->qla4_82xx_reg->host_status);
	else if (is_qla8032(ha) || is_qla8042(ha))
		reg_val = qla4_8xxx_rd_direct(ha, QLA8XXX_PEG_ALIVE_COUNTER);
	else
		reg_val = readw(&ha->reg->ctrl_status);

	if (reg_val == QL4_ISP_REG_DISCONNECT)
		rval = QLA_ERROR;

	return rval;
}