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
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;

/* Variables and functions */
 int qla2x00_check_reg32_for_disconnect (int /*<<< orphan*/ *,int) ; 

bool
qla2x00_check_reg16_for_disconnect(scsi_qla_host_t *vha, uint16_t reg)
{
	return qla2x00_check_reg32_for_disconnect(vha, 0xffff0000 | reg);
}