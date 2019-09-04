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
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 int QLA_SUCCESS ; 
 scalar_t__ is_qla8022 (struct scsi_qla_host*) ; 
 scalar_t__ is_qla8032 (struct scsi_qla_host*) ; 
 scalar_t__ is_qla8042 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_82xx_get_fdt_info (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_82xx_get_idc_param (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_83xx_get_idc_param (struct scsi_qla_host*) ; 
 int qla4_8xxx_find_flt_start (struct scsi_qla_host*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla4_8xxx_get_flt_info (struct scsi_qla_host*,int /*<<< orphan*/ ) ; 

int
qla4_8xxx_get_flash_info(struct scsi_qla_host *ha)
{
	int ret;
	uint32_t flt_addr;

	ret = qla4_8xxx_find_flt_start(ha, &flt_addr);
	if (ret != QLA_SUCCESS)
		return ret;

	qla4_8xxx_get_flt_info(ha, flt_addr);
	if (is_qla8022(ha)) {
		qla4_82xx_get_fdt_info(ha);
		qla4_82xx_get_idc_param(ha);
	} else if (is_qla8032(ha) || is_qla8042(ha)) {
		qla4_83xx_get_idc_param(ha);
	}

	return QLA_SUCCESS;
}