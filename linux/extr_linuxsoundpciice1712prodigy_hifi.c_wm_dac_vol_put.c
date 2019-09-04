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
struct snd_ice1712 {int /*<<< orphan*/  gpio_mutex; struct prodigy_hifi_spec* spec; } ;
struct TYPE_3__ {int /*<<< orphan*/ * value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct prodigy_hifi_spec {int /*<<< orphan*/ * master; int /*<<< orphan*/ * vol; } ;

/* Variables and functions */
 int WM_DAC_ATTEN_L ; 
 int /*<<< orphan*/  WM_VOL_MUTE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  wm_set_vol (struct snd_ice1712*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm_dac_vol_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	struct prodigy_hifi_spec *spec = ice->spec;
	int i, idx, change = 0;

	mutex_lock(&ice->gpio_mutex);
	for (i = 0; i < 2; i++) {
		if (ucontrol->value.integer.value[i] != spec->vol[2 + i]) {
			idx = WM_DAC_ATTEN_L + i;
			spec->vol[2 + i] &= WM_VOL_MUTE;
			spec->vol[2 + i] |= ucontrol->value.integer.value[i];
			wm_set_vol(ice, idx, spec->vol[2 + i], spec->master[i]);
			change = 1;
		}
	}
	mutex_unlock(&ice->gpio_mutex);
	return change;
}