#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int max; scalar_t__ min; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_info {int count; TYPE_2__ value; void* type; } ;

/* Variables and functions */
 int AUDIO_DEST_MAX ; 
 int CTRL_VOL_MAX ; 
 scalar_t__ CTRL_VOL_MIN ; 
 scalar_t__ PCM_PLAYBACK_DEVICE ; 
 scalar_t__ PCM_PLAYBACK_MUTE ; 
 scalar_t__ PCM_PLAYBACK_VOLUME ; 
 void* SNDRV_CTL_ELEM_TYPE_BOOLEAN ; 
 void* SNDRV_CTL_ELEM_TYPE_INTEGER ; 

__attribute__((used)) static int snd_bcm2835_ctl_info(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_info *uinfo)
{
	if (kcontrol->private_value == PCM_PLAYBACK_VOLUME) {
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
		uinfo->count = 1;
		uinfo->value.integer.min = CTRL_VOL_MIN;
		uinfo->value.integer.max = CTRL_VOL_MAX; /* 2303 */
	} else if (kcontrol->private_value == PCM_PLAYBACK_MUTE) {
		uinfo->type = SNDRV_CTL_ELEM_TYPE_BOOLEAN;
		uinfo->count = 1;
		uinfo->value.integer.min = 0;
		uinfo->value.integer.max = 1;
	} else if (kcontrol->private_value == PCM_PLAYBACK_DEVICE) {
		uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
		uinfo->count = 1;
		uinfo->value.integer.min = 0;
		uinfo->value.integer.max = AUDIO_DEST_MAX - 1;
	}
	return 0;
}