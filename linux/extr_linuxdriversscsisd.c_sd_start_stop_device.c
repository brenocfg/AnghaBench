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
struct scsi_sense_hdr {int asc; } ;
struct scsi_disk {struct scsi_device* device; } ;
struct scsi_device {scalar_t__ start_stop_pwr_cond; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 scalar_t__ DRIVER_SENSE ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  RQF_PM ; 
 int /*<<< orphan*/  SD_MAX_RETRIES ; 
 int /*<<< orphan*/  SD_TIMEOUT ; 
 unsigned char START_STOP ; 
 scalar_t__ driver_byte (int) ; 
 int /*<<< orphan*/  scsi_device_online (struct scsi_device*) ; 
 int scsi_execute (struct scsi_device*,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct scsi_sense_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ scsi_sense_valid (struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  sd_print_result (struct scsi_disk*,char*,int) ; 
 int /*<<< orphan*/  sd_print_sense_hdr (struct scsi_disk*,struct scsi_sense_hdr*) ; 

__attribute__((used)) static int sd_start_stop_device(struct scsi_disk *sdkp, int start)
{
	unsigned char cmd[6] = { START_STOP };	/* START_VALID */
	struct scsi_sense_hdr sshdr;
	struct scsi_device *sdp = sdkp->device;
	int res;

	if (start)
		cmd[4] |= 1;	/* START */

	if (sdp->start_stop_pwr_cond)
		cmd[4] |= start ? 1 << 4 : 3 << 4;	/* Active or Standby */

	if (!scsi_device_online(sdp))
		return -ENODEV;

	res = scsi_execute(sdp, cmd, DMA_NONE, NULL, 0, NULL, &sshdr,
			SD_TIMEOUT, SD_MAX_RETRIES, 0, RQF_PM, NULL);
	if (res) {
		sd_print_result(sdkp, "Start/Stop Unit failed", res);
		if (driver_byte(res) == DRIVER_SENSE)
			sd_print_sense_hdr(sdkp, &sshdr);
		if (scsi_sense_valid(&sshdr) &&
			/* 0x3a is medium not present */
			sshdr.asc == 0x3a)
			res = 0;
	}

	/* SCSI error codes must not go to the generic layer */
	if (res)
		return -EIO;

	return 0;
}