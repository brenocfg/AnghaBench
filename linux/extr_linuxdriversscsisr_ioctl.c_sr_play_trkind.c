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
struct scsi_cd {int dummy; } ;
struct packet_command {int /*<<< orphan*/  data_direction; int /*<<< orphan*/ * cmd; int /*<<< orphan*/  timeout; } ;
struct cdrom_ti {int /*<<< orphan*/  cdti_ind1; int /*<<< orphan*/  cdti_trk1; int /*<<< orphan*/  cdti_ind0; int /*<<< orphan*/  cdti_trk0; } ;
struct cdrom_device_info {struct scsi_cd* handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int EDRIVE_CANT_DO_THIS ; 
 int /*<<< orphan*/  GPCMD_PLAYAUDIO_TI ; 
 int /*<<< orphan*/  IOCTL_TIMEOUT ; 
 int /*<<< orphan*/  memset (struct packet_command*,int /*<<< orphan*/ ,int) ; 
 int sr_do_ioctl (struct scsi_cd*,struct packet_command*) ; 
 int sr_fake_playtrkind (struct cdrom_device_info*,struct cdrom_ti*) ; 

__attribute__((used)) static int sr_play_trkind(struct cdrom_device_info *cdi,
		struct cdrom_ti *ti)

{
	struct scsi_cd *cd = cdi->handle;
	struct packet_command cgc;
	int result;

	memset(&cgc, 0, sizeof(struct packet_command));
	cgc.timeout = IOCTL_TIMEOUT;
	cgc.cmd[0] = GPCMD_PLAYAUDIO_TI;
	cgc.cmd[4] = ti->cdti_trk0;
	cgc.cmd[5] = ti->cdti_ind0;
	cgc.cmd[7] = ti->cdti_trk1;
	cgc.cmd[8] = ti->cdti_ind1;
	cgc.data_direction = DMA_NONE;

	result = sr_do_ioctl(cd, &cgc);
	if (result == -EDRIVE_CANT_DO_THIS)
		result = sr_fake_playtrkind(cdi, ti);

	return result;
}