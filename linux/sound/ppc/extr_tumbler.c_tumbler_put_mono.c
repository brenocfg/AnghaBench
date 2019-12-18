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
struct tumbler_mono_vol {unsigned int max; size_t index; } ;
struct snd_pmac {struct pmac_tumbler* mixer_data; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct pmac_tumbler {unsigned int* mono_vol; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 struct snd_pmac* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  tumbler_set_mono_volume (struct pmac_tumbler*,struct tumbler_mono_vol*) ; 

__attribute__((used)) static int tumbler_put_mono(struct snd_kcontrol *kcontrol,
			    struct snd_ctl_elem_value *ucontrol)
{
	struct tumbler_mono_vol *info = (struct tumbler_mono_vol *)kcontrol->private_value;
	struct snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	struct pmac_tumbler *mix;
	unsigned int vol;
	int change;

	if (! (mix = chip->mixer_data))
		return -ENODEV;
	vol = ucontrol->value.integer.value[0];
	if (vol >= info->max)
		return -EINVAL;
	change = mix->mono_vol[info->index] != vol;
	if (change) {
		mix->mono_vol[info->index] = vol;
		tumbler_set_mono_volume(mix, info);
	}
	return change;
}