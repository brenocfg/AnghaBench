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
struct scsi_sense_hdr {scalar_t__ sense_key; } ;
struct scsi_device {int changed; scalar_t__ removable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 char TEST_UNIT_READY ; 
 scalar_t__ UNIT_ATTENTION ; 
 int scsi_execute_req (struct scsi_device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct scsi_sense_hdr*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ scsi_sense_valid (struct scsi_sense_hdr*) ; 

int
scsi_test_unit_ready(struct scsi_device *sdev, int timeout, int retries,
		     struct scsi_sense_hdr *sshdr)
{
	char cmd[] = {
		TEST_UNIT_READY, 0, 0, 0, 0, 0,
	};
	int result;

	/* try to eat the UNIT_ATTENTION if there are enough retries */
	do {
		result = scsi_execute_req(sdev, cmd, DMA_NONE, NULL, 0, sshdr,
					  timeout, 1, NULL);
		if (sdev->removable && scsi_sense_valid(sshdr) &&
		    sshdr->sense_key == UNIT_ATTENTION)
			sdev->changed = 1;
	} while (scsi_sense_valid(sshdr) &&
		 sshdr->sense_key == UNIT_ATTENTION && --retries);

	return result;
}