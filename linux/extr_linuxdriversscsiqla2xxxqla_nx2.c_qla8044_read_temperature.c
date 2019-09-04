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
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLA8044_CRB_TEMP_STATE_INDEX ; 
 int /*<<< orphan*/  qla8044_rd_direct (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int qla82xx_get_temp_val (int /*<<< orphan*/ ) ; 

int qla8044_read_temperature(scsi_qla_host_t *vha)
{
	uint32_t temp;

	temp = qla8044_rd_direct(vha, QLA8044_CRB_TEMP_STATE_INDEX);
	return qla82xx_get_temp_val(temp);
}