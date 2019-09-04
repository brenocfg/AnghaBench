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
struct scsi_disk {scalar_t__ capacity; } ;
struct scsi_device {scalar_t__ removable; } ;

/* Variables and functions */
 scalar_t__ DRIVER_SENSE ; 
 int /*<<< orphan*/  KERN_NOTICE ; 
 scalar_t__ NOT_READY ; 
 scalar_t__ driver_byte (int) ; 
 int /*<<< orphan*/  sd_print_sense_hdr (struct scsi_disk*,struct scsi_sense_hdr*) ; 
 int /*<<< orphan*/  sd_printk (int /*<<< orphan*/ ,struct scsi_disk*,char*) ; 
 int /*<<< orphan*/  set_media_not_present (struct scsi_disk*) ; 

__attribute__((used)) static void read_capacity_error(struct scsi_disk *sdkp, struct scsi_device *sdp,
			struct scsi_sense_hdr *sshdr, int sense_valid,
			int the_result)
{
	if (driver_byte(the_result) == DRIVER_SENSE)
		sd_print_sense_hdr(sdkp, sshdr);
	else
		sd_printk(KERN_NOTICE, sdkp, "Sense not available.\n");

	/*
	 * Set dirty bit for removable devices if not ready -
	 * sometimes drives will not report this properly.
	 */
	if (sdp->removable &&
	    sense_valid && sshdr->sense_key == NOT_READY)
		set_media_not_present(sdkp);

	/*
	 * We used to set media_present to 0 here to indicate no media
	 * in the drive, but some drives fail read capacity even with
	 * media present, so we can't do that.
	 */
	sdkp->capacity = 0; /* unknown mapped to zero - as usual */
}