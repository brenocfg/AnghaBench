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
struct snd_line6_pcm {scalar_t__* volume_playback; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {scalar_t__* value; } ;
struct TYPE_3__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;

/* Variables and functions */
 struct snd_line6_pcm* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_line6_control_playback_put(struct snd_kcontrol *kcontrol,
					  struct snd_ctl_elem_value *ucontrol)
{
	int i, changed = 0;
	struct snd_line6_pcm *line6pcm = snd_kcontrol_chip(kcontrol);

	for (i = 0; i < 2; i++)
		if (line6pcm->volume_playback[i] !=
		    ucontrol->value.integer.value[i]) {
			line6pcm->volume_playback[i] =
			    ucontrol->value.integer.value[i];
			changed = 1;
		}

	return changed;
}