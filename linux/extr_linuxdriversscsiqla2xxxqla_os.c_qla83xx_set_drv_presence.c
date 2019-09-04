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
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int QLA_SUCCESS ; 
 int __qla83xx_set_drv_presence (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla83xx_idc_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla83xx_idc_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
qla83xx_set_drv_presence(scsi_qla_host_t *vha)
{
	int rval = QLA_SUCCESS;

	qla83xx_idc_lock(vha, 0);
	rval = __qla83xx_set_drv_presence(vha);
	qla83xx_idc_unlock(vha, 0);

	return rval;
}