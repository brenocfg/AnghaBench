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
struct cdrom_device_info {int dummy; } ;

/* Variables and functions */
#define  CDROMPLAYTRKIND 130 
#define  CDROMREADTOCENTRY 129 
#define  CDROMREADTOCHDR 128 
 int EINVAL ; 
 int sr_play_trkind (struct cdrom_device_info*,void*) ; 
 int sr_read_tocentry (struct cdrom_device_info*,void*) ; 
 int sr_read_tochdr (struct cdrom_device_info*,void*) ; 

int sr_audio_ioctl(struct cdrom_device_info *cdi, unsigned int cmd, void *arg)
{
	switch (cmd) {
	case CDROMREADTOCHDR:
		return sr_read_tochdr(cdi, arg);
	case CDROMREADTOCENTRY:
		return sr_read_tocentry(cdi, arg);
	case CDROMPLAYTRKIND:
		return sr_play_trkind(cdi, arg);
	default:
		return -EINVAL;
	}
}