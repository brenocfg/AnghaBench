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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  CRB_TEMP_STATE ; 
 int qla82xx_get_temp_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla82xx_rd_32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int qla82xx_read_temperature(scsi_qla_host_t *vha)
{
	uint32_t temp;

	temp = qla82xx_rd_32(vha->hw, CRB_TEMP_STATE);
	return qla82xx_get_temp_val(temp);
}