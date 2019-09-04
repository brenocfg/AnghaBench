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
struct snd_pcxhr {int* digital_capture_volume; int** digital_playback_volume; TYPE_3__* mgr; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_4__ {int* value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  mixer_mutex; } ;

/* Variables and functions */
 int PCXHR_DIGITAL_LEVEL_MAX ; 
 int PCXHR_DIGITAL_LEVEL_MIN ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcxhr_update_audio_pipe_level (struct snd_pcxhr*,int,int) ; 
 int /*<<< orphan*/  pcxhr_update_playback_stream_level (struct snd_pcxhr*,int) ; 
 int snd_ctl_get_ioffidx (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 struct snd_pcxhr* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int pcxhr_pcm_vol_put(struct snd_kcontrol *kcontrol,
			     struct snd_ctl_elem_value *ucontrol)
{
	struct snd_pcxhr *chip = snd_kcontrol_chip(kcontrol);
	int idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id);	/* index */
	int changed = 0;
	int is_capture = kcontrol->private_value;
	int *stored_volume;
	int i;

	mutex_lock(&chip->mgr->mixer_mutex);
	if (is_capture)		/* digital capture */
		stored_volume = chip->digital_capture_volume;
	else			/* digital playback */
		stored_volume = chip->digital_playback_volume[idx];
	for (i = 0; i < 2; i++) {
		int vol = ucontrol->value.integer.value[i];
		if (vol < PCXHR_DIGITAL_LEVEL_MIN ||
		    vol > PCXHR_DIGITAL_LEVEL_MAX)
			continue;
		if (stored_volume[i] != vol) {
			stored_volume[i] = vol;
			changed = 1;
			if (is_capture)	/* update capture volume */
				pcxhr_update_audio_pipe_level(chip, 1, i);
		}
	}
	if (!is_capture && changed)	/* update playback volume */
		pcxhr_update_playback_stream_level(chip, idx);
	mutex_unlock(&chip->mgr->mixer_mutex);
	return changed;
}