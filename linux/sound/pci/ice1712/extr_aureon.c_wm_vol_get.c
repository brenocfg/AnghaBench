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
struct snd_ice1712 {struct aureon_spec* spec; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct aureon_spec {int* vol; } ;

/* Variables and functions */
 int WM_VOL_MUTE ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int wm_vol_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	struct aureon_spec *spec = ice->spec;
	int i, ofs, voices;

	voices = kcontrol->private_value >> 8;
	ofs = kcontrol->private_value & 0xff;
	for (i = 0; i < voices; i++)
		ucontrol->value.integer.value[i] =
			spec->vol[ofs+i] & ~WM_VOL_MUTE;
	return 0;
}