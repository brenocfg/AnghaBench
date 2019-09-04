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
struct qla_hw_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_QLA8044 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA82XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla8044_clear_drv_active (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla8044_idc_lock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla8044_idc_unlock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_clear_drv_active (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_idc_lock (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla82xx_idc_unlock (struct qla_hw_data*) ; 

__attribute__((used)) static void
qla2x00_clear_drv_active(struct qla_hw_data *ha)
{
	if (IS_QLA8044(ha)) {
		qla8044_idc_lock(ha);
		qla8044_clear_drv_active(ha);
		qla8044_idc_unlock(ha);
	} else if (IS_QLA82XX(ha)) {
		qla82xx_idc_lock(ha);
		qla82xx_clear_drv_active(ha);
		qla82xx_idc_unlock(ha);
	}
}