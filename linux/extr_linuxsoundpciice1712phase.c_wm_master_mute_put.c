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
struct snd_kcontrol {int dummy; } ;
struct snd_ice1712 {int num_total_dacs; struct phase28_spec* spec; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct phase28_spec {int* master; int /*<<< orphan*/ * vol; } ;

/* Variables and functions */
 scalar_t__ WM_DAC_ATTEN ; 
 int WM_VOL_MUTE ; 
 int /*<<< orphan*/  snd_ice1712_restore_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_save_gpio_status (struct snd_ice1712*) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  wm_set_vol (struct snd_ice1712*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm_master_mute_put(struct snd_kcontrol *kcontrol,
				struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	struct phase28_spec *spec = ice->spec;
	int change = 0, i;

	snd_ice1712_save_gpio_status(ice);
	for (i = 0; i < 2; i++) {
		int val = (spec->master[i] & WM_VOL_MUTE) ? 0 : 1;
		if (ucontrol->value.integer.value[i] != val) {
			int dac;
			spec->master[i] &= ~WM_VOL_MUTE;
			spec->master[i] |=
				ucontrol->value.integer.value[i] ? 0 :
				WM_VOL_MUTE;
			for (dac = 0; dac < ice->num_total_dacs; dac += 2)
				wm_set_vol(ice, WM_DAC_ATTEN + dac + i,
						spec->vol[dac + i],
						spec->master[i]);
			change = 1;
		}
	}
	snd_ice1712_restore_gpio_status(ice);

	return change;
}