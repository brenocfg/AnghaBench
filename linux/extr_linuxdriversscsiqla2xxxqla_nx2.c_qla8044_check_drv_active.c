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
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct qla_hw_data {int portnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLA8044_CRB_DRV_ACTIVE_INDEX ; 
 int QLA_SUCCESS ; 
 int QLA_TEST_FAILED ; 
 int qla8044_rd_direct (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qla8044_check_drv_active(struct scsi_qla_host *vha)
{
	uint32_t drv_active;
	struct qla_hw_data *ha = vha->hw;

	drv_active = qla8044_rd_direct(vha, QLA8044_CRB_DRV_ACTIVE_INDEX);
	if (drv_active & (1 << ha->portnum))
		return QLA_SUCCESS;
	else
		return QLA_TEST_FAILED;
}