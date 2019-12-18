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
struct snd_pmac {struct pmac_tumbler* mixer_data; } ;
struct snd_kcontrol {scalar_t__ private_value; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct pmac_tumbler {int /*<<< orphan*/ ** mix_vol; } ;

/* Variables and functions */
 int ENODEV ; 
 struct snd_pmac* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snapper_get_mix(struct snd_kcontrol *kcontrol,
			   struct snd_ctl_elem_value *ucontrol)
{
	int idx = (int)kcontrol->private_value;
	struct snd_pmac *chip = snd_kcontrol_chip(kcontrol);
	struct pmac_tumbler *mix;
	if (! (mix = chip->mixer_data))
		return -ENODEV;
	ucontrol->value.integer.value[0] = mix->mix_vol[idx][0];
	ucontrol->value.integer.value[1] = mix->mix_vol[idx][1];
	return 0;
}