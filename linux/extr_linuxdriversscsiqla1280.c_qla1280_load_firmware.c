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
struct scsi_qla_host {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ISP1040 (struct scsi_qla_host*) ; 
 int qla1280_chip_diag (struct scsi_qla_host*) ; 
 int qla1280_load_firmware_dma (struct scsi_qla_host*) ; 
 int qla1280_load_firmware_pio (struct scsi_qla_host*) ; 
 int qla1280_start_firmware (struct scsi_qla_host*) ; 

__attribute__((used)) static int
qla1280_load_firmware(struct scsi_qla_host *ha)
{
	/* enter with host_lock taken */
	int err;

	err = qla1280_chip_diag(ha);
	if (err)
		goto out;
	if (IS_ISP1040(ha))
		err = qla1280_load_firmware_pio(ha);
	else
		err = qla1280_load_firmware_dma(ha);
	if (err)
		goto out;
	err = qla1280_start_firmware(ha);
 out:
	return err;
}