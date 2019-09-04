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
struct packet_command {int* cmd; int /*<<< orphan*/  timeout; int /*<<< orphan*/  data_direction; } ;
struct cdrom_device_info {int /*<<< orphan*/ * handle; } ;
typedef  int /*<<< orphan*/  Scsi_CD ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_NONE ; 
 int EIO ; 
 int GPCMD_SET_SPEED ; 
 int /*<<< orphan*/  IOCTL_TIMEOUT ; 
 int /*<<< orphan*/  memset (struct packet_command*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sr_do_ioctl (int /*<<< orphan*/ *,struct packet_command*) ; 

int sr_select_speed(struct cdrom_device_info *cdi, int speed)
{
	Scsi_CD *cd = cdi->handle;
	struct packet_command cgc;

	if (speed == 0)
		speed = 0xffff;	/* set to max */
	else
		speed *= 177;	/* Nx to kbyte/s */

	memset(&cgc, 0, sizeof(struct packet_command));
	cgc.cmd[0] = GPCMD_SET_SPEED;	/* SET CD SPEED */
	cgc.cmd[2] = (speed >> 8) & 0xff;	/* MSB for speed (in kbytes/sec) */
	cgc.cmd[3] = speed & 0xff;	/* LSB */
	cgc.data_direction = DMA_NONE;
	cgc.timeout = IOCTL_TIMEOUT;

	if (sr_do_ioctl(cd, &cgc))
		return -EIO;
	return 0;
}