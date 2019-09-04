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
struct scsi_disk {int security; struct scsi_device* device; } ;
struct scsi_device {int /*<<< orphan*/  security_supported; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_BUF_SIZE ; 
 int /*<<< orphan*/  SECURITY_PROTOCOL_IN ; 
 int /*<<< orphan*/  SECURITY_PROTOCOL_OUT ; 
 int scsi_report_opcode (struct scsi_device*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sd_read_security(struct scsi_disk *sdkp, unsigned char *buffer)
{
	struct scsi_device *sdev = sdkp->device;

	if (!sdev->security_supported)
		return;

	if (scsi_report_opcode(sdev, buffer, SD_BUF_SIZE,
			SECURITY_PROTOCOL_IN) == 1 &&
	    scsi_report_opcode(sdev, buffer, SD_BUF_SIZE,
			SECURITY_PROTOCOL_OUT) == 1)
		sdkp->security = 1;
}