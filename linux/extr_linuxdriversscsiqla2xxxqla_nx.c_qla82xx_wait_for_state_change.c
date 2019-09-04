#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct qla_hw_data {int dummy; } ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA82XX_CRB_DEV_STATE ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  qla82xx_idc_lock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_idc_unlock (struct qla_hw_data*) ; 
 scalar_t__ qla82xx_rd_32 (struct qla_hw_data*,int /*<<< orphan*/ ) ; 

uint32_t
qla82xx_wait_for_state_change(scsi_qla_host_t *vha, uint32_t curr_state)
{
	struct qla_hw_data *ha = vha->hw;
	uint32_t dev_state;

	do {
		msleep(1000);
		qla82xx_idc_lock(ha);
		dev_state = qla82xx_rd_32(ha, QLA82XX_CRB_DEV_STATE);
		qla82xx_idc_unlock(ha);
	} while (dev_state == curr_state);

	return dev_state;
}