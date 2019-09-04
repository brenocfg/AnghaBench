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
struct scsi_device {scalar_t__ no_read_disc_info; } ;
struct scsi_cd {struct scsi_device* device; } ;
struct packet_command {scalar_t__* cmd; scalar_t__ timeout; int stat; } ;
struct cdrom_device_info {struct scsi_cd* handle; } ;

/* Variables and functions */
 int EDRIVE_CANT_DO_THIS ; 
 scalar_t__ GPCMD_READ_DISC_INFO ; 
 scalar_t__ IOCTL_TIMEOUT ; 
 int /*<<< orphan*/  sr_do_ioctl (struct scsi_cd*,struct packet_command*) ; 

__attribute__((used)) static int sr_packet(struct cdrom_device_info *cdi,
		struct packet_command *cgc)
{
	struct scsi_cd *cd = cdi->handle;
	struct scsi_device *sdev = cd->device;

	if (cgc->cmd[0] == GPCMD_READ_DISC_INFO && sdev->no_read_disc_info)
		return -EDRIVE_CANT_DO_THIS;

	if (cgc->timeout <= 0)
		cgc->timeout = IOCTL_TIMEOUT;

	sr_do_ioctl(cd, cgc);

	return cgc->stat;
}