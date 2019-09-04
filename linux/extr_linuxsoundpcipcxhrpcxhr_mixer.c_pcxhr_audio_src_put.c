#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_pcxhr {int audio_capture_source; TYPE_3__* mgr; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {int* item; } ;
struct TYPE_5__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct TYPE_6__ {int /*<<< orphan*/  mixer_mutex; scalar_t__ is_hr_stereo; scalar_t__ board_has_mic; scalar_t__ board_has_aes1; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  hr222_set_audio_source (struct snd_pcxhr*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcxhr_set_audio_source (struct snd_pcxhr*) ; 
 struct snd_pcxhr* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int pcxhr_audio_src_put(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	int ret = 0;
	int i = 2;		/* no SRC, no Mic available */
	if (chip->mgr->board_has_aes1) {
		i = 3;		/* SRC available */
		if (chip->mgr->board_has_mic)
			i = 5;	/* Mic and MicroMix available */
	}
	if (ucontrol->value.enumerated.item[0] >= i)
		return -EINVAL;
	mutex_lock(&chip->mgr->mixer_mutex);
	if (chip->audio_capture_source != ucontrol->value.enumerated.item[0]) {
		chip->audio_capture_source = ucontrol->value.enumerated.item[0];
		if (chip->mgr->is_hr_stereo)
			hr222_set_audio_source(chip);
		else
			pcxhr_set_audio_source(chip);
		ret = 1;
	}
	mutex_unlock(&chip->mgr->mixer_mutex);
	return ret;
}