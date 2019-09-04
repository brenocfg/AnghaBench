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
typedef  size_t uint32_t ;
struct qla_hw_data {int dummy; } ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 size_t cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flash_data_addr (struct qla_hw_data*,size_t) ; 
 int /*<<< orphan*/  qla24xx_read_flash_dword (struct qla_hw_data*,int /*<<< orphan*/ ) ; 

uint32_t *
qla24xx_read_flash_data(scsi_qla_host_t *vha, uint32_t *dwptr, uint32_t faddr,
    uint32_t dwords)
{
	uint32_t i;
	struct qla_hw_data *ha = vha->hw;

	/* Dword reads to flash. */
	for (i = 0; i < dwords; i++, faddr++)
		dwptr[i] = cpu_to_le32(qla24xx_read_flash_dword(ha,
		    flash_data_addr(ha, faddr)));

	return dwptr;
}