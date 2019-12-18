#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct snd_i2c_device {TYPE_3__* bus; struct cs8427* private_data; } ;
struct TYPE_6__ {char* pcm_status; TYPE_1__* pcm_ctl; } ;
struct cs8427 {unsigned int rate; TYPE_2__ playback; } ;
struct TYPE_7__ {int /*<<< orphan*/  card; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENXIO ; 
 char IEC958_AES0_PROFESSIONAL ; 
 char IEC958_AES0_PRO_FS ; 
 char IEC958_AES0_PRO_FS_32000 ; 
 char IEC958_AES0_PRO_FS_44100 ; 
 char IEC958_AES0_PRO_FS_48000 ; 
 char IEC958_AES0_PRO_FS_NOTID ; 
 char IEC958_AES3_CON_FS ; 
 char IEC958_AES3_CON_FS_32000 ; 
 char IEC958_AES3_CON_FS_44100 ; 
 char IEC958_AES3_CON_FS_48000 ; 
 int /*<<< orphan*/  SNDRV_CTL_EVENT_MASK_VALUE ; 
 scalar_t__ snd_BUG_ON (int) ; 
 int /*<<< orphan*/  snd_cs8427_reset (struct snd_i2c_device*) ; 
 int snd_cs8427_send_corudata (struct snd_i2c_device*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snd_ctl_notify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_i2c_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  snd_i2c_unlock (TYPE_3__*) ; 

int snd_cs8427_iec958_pcm(struct snd_i2c_device *cs8427, unsigned int rate)
{
	struct cs8427 *chip;
	char *status;
	int err, reset;

	if (snd_BUG_ON(!cs8427))
		return -ENXIO;
	chip = cs8427->private_data;
	status = chip->playback.pcm_status;
	snd_i2c_lock(cs8427->bus);
	if (status[0] & IEC958_AES0_PROFESSIONAL) {
		status[0] &= ~IEC958_AES0_PRO_FS;
		switch (rate) {
		case 32000: status[0] |= IEC958_AES0_PRO_FS_32000; break;
		case 44100: status[0] |= IEC958_AES0_PRO_FS_44100; break;
		case 48000: status[0] |= IEC958_AES0_PRO_FS_48000; break;
		default: status[0] |= IEC958_AES0_PRO_FS_NOTID; break;
		}
	} else {
		status[3] &= ~IEC958_AES3_CON_FS;
		switch (rate) {
		case 32000: status[3] |= IEC958_AES3_CON_FS_32000; break;
		case 44100: status[3] |= IEC958_AES3_CON_FS_44100; break;
		case 48000: status[3] |= IEC958_AES3_CON_FS_48000; break;
		}
	}
	err = snd_cs8427_send_corudata(cs8427, 0, status, 24);
	if (err > 0)
		snd_ctl_notify(cs8427->bus->card,
			       SNDRV_CTL_EVENT_MASK_VALUE,
			       &chip->playback.pcm_ctl->id);
	reset = chip->rate != rate;
	chip->rate = rate;
	snd_i2c_unlock(cs8427->bus);
	if (reset)
		snd_cs8427_reset(cs8427);
	return err < 0 ? err : 0;
}