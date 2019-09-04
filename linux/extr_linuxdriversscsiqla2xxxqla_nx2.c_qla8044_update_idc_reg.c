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
struct TYPE_2__ {scalar_t__ init_done; } ;
struct scsi_qla_host {TYPE_1__ flags; struct qla_hw_data* hw; } ;
struct qla_hw_data {int portnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLA8044_CRB_DRV_ACTIVE_INDEX ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  ql2xdontresethba ; 
 int /*<<< orphan*/  qla8044_clear_drv_active (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla8044_clear_idc_dontreset (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla8044_idc_lock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla8044_idc_unlock (struct qla_hw_data*) ; 
 int qla8044_rd_direct (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla8044_set_drv_active (struct scsi_qla_host*) ; 
 int qla8044_set_idc_ver (struct scsi_qla_host*) ; 

__attribute__((used)) static int
qla8044_update_idc_reg(struct scsi_qla_host *vha)
{
	uint32_t drv_active;
	int rval = QLA_SUCCESS;
	struct qla_hw_data *ha = vha->hw;

	if (vha->flags.init_done)
		goto exit_update_idc_reg;

	qla8044_idc_lock(ha);
	qla8044_set_drv_active(vha);

	drv_active = qla8044_rd_direct(vha,
	    QLA8044_CRB_DRV_ACTIVE_INDEX);

	/* If we are the first driver to load and
	 * ql2xdontresethba is not set, clear IDC_CTRL BIT0. */
	if ((drv_active == (1 << ha->portnum)) && !ql2xdontresethba)
		qla8044_clear_idc_dontreset(vha);

	rval = qla8044_set_idc_ver(vha);
	if (rval == QLA_FUNCTION_FAILED)
		qla8044_clear_drv_active(ha);
	qla8044_idc_unlock(ha);

exit_update_idc_reg:
	return rval;
}