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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct qla_hw_data {int md_template_size; scalar_t__ md_tmplt_hdr; } ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */

int
qla82xx_validate_template_chksum(scsi_qla_host_t *vha)
{
	struct qla_hw_data *ha = vha->hw;
	uint64_t chksum = 0;
	uint32_t *d_ptr = (uint32_t *)ha->md_tmplt_hdr;
	int count = ha->md_template_size/sizeof(uint32_t);

	while (count-- > 0)
		chksum += *d_ptr++;
	while (chksum >> 32)
		chksum = (chksum & 0xFFFFFFFF) + (chksum >> 32);
	return ~chksum;
}