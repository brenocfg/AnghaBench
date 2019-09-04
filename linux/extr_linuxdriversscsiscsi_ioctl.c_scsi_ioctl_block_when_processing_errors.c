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
struct scsi_device {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int SG_SCSI_RESET ; 
 int /*<<< orphan*/  scsi_block_when_processing_errors (struct scsi_device*) ; 
 scalar_t__ scsi_host_in_recovery (int /*<<< orphan*/ ) ; 

int scsi_ioctl_block_when_processing_errors(struct scsi_device *sdev, int cmd,
		bool ndelay)
{
	if (cmd == SG_SCSI_RESET && ndelay) {
		if (scsi_host_in_recovery(sdev->host))
			return -EAGAIN;
	} else {
		if (!scsi_block_when_processing_errors(sdev))
			return -ENODEV;
	}

	return 0;
}