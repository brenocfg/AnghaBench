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
typedef  size_t uint32_t ;
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct qla_hw_data {int dummy; } ;

/* Variables and functions */
 size_t const CRB_REG_INDEX_MAX ; 
 int /*<<< orphan*/ * qla8044_reg_tbl ; 
 int /*<<< orphan*/  qla8044_wr_reg (struct qla_hw_data*,int /*<<< orphan*/ ,size_t const) ; 

void
qla8044_wr_direct(struct scsi_qla_host *vha,
	const uint32_t crb_reg,
	const uint32_t value)
{
	struct qla_hw_data *ha = vha->hw;

	if (crb_reg < CRB_REG_INDEX_MAX)
		qla8044_wr_reg(ha, qla8044_reg_tbl[crb_reg], value);
}