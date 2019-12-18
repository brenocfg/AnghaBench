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
struct snd_pcm_chmap {int /*<<< orphan*/  chmap; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {scalar_t__* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_ac97 {struct snd_pcm_chmap** chmaps; } ;

/* Variables and functions */
 size_t SNDRV_PCM_STREAM_PLAYBACK ; 
 int snd_ac97_put_volsw (struct snd_kcontrol*,struct snd_ctl_elem_value*) ; 
 struct snd_ac97* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  snd_pcm_alt_chmaps ; 
 int /*<<< orphan*/  snd_pcm_std_chmaps ; 

__attribute__((used)) static int alc650_swap_surround_put(struct snd_kcontrol *kcontrol,
				    struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ac97 *ac97 = snd_kcontrol_chip(kcontrol);
	struct snd_pcm_chmap *map = ac97->chmaps[SNDRV_PCM_STREAM_PLAYBACK];

	if (map) {
		if (ucontrol->value.integer.value[0])
			map->chmap = snd_pcm_std_chmaps;
		else
			map->chmap = snd_pcm_alt_chmaps;
	}
	return snd_ac97_put_volsw(kcontrol, ucontrol);
}