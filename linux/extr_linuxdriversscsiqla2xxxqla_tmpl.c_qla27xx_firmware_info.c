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
struct scsi_qla_host {TYPE_1__* hw; } ;
struct qla27xx_fwdt_template {int* firmware_version; } ;
struct TYPE_2__ {int fw_major_version; int fw_minor_version; int fw_subminor_version; int fw_attributes_h; int fw_attributes; int* fw_attributes_ext; } ;

/* Variables and functions */

__attribute__((used)) static void
qla27xx_firmware_info(struct qla27xx_fwdt_template *tmp,
	struct scsi_qla_host *vha)
{
	tmp->firmware_version[0] = vha->hw->fw_major_version;
	tmp->firmware_version[1] = vha->hw->fw_minor_version;
	tmp->firmware_version[2] = vha->hw->fw_subminor_version;
	tmp->firmware_version[3] =
	    vha->hw->fw_attributes_h << 16 | vha->hw->fw_attributes;
	tmp->firmware_version[4] =
	    vha->hw->fw_attributes_ext[1] << 16 | vha->hw->fw_attributes_ext[0];
}