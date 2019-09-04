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
struct snd_kcontrol {int private_value; } ;
struct snd_ice1712 {struct phase28_spec* spec; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct phase28_spec {int* vol; int /*<<< orphan*/ * master; } ;

/* Variables and functions */
 int WM_VOL_MUTE ; 
 int /*<<< orphan*/  snd_ice1712_restore_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_save_gpio_status (struct snd_ice1712*) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  wm_set_vol (struct snd_ice1712*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm_mute_put(struct snd_kcontrol *kcontrol,
			struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	struct phase28_spec *spec = ice->spec;
	int change = 0, voices, ofs, i;

	voices = kcontrol->private_value >> 8;
	ofs = kcontrol->private_value & 0xFF;

	snd_ice1712_save_gpio_status(ice);
	for (i = 0; i < voices; i++) {
		int val = (spec->vol[ofs + i] & WM_VOL_MUTE) ? 0 : 1;
		if (ucontrol->value.integer.value[i] != val) {
			spec->vol[ofs + i] &= ~WM_VOL_MUTE;
			spec->vol[ofs + i] |=
				ucontrol->value.integer.value[i] ? 0 :
				WM_VOL_MUTE;
			wm_set_vol(ice, ofs + i, spec->vol[ofs + i],
					spec->master[i]);
			change = 1;
		}
	}
	snd_ice1712_restore_gpio_status(ice);

	return change;
}