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
struct via82xx {int port; unsigned char** playback_volume; } ;
struct TYPE_4__ {unsigned int subdevice; } ;
struct snd_kcontrol {TYPE_1__ id; } ;
struct TYPE_5__ {unsigned char* value; } ;
struct TYPE_6__ {TYPE_2__ integer; } ;
struct snd_ctl_elem_value {TYPE_3__ value; } ;

/* Variables and functions */
 unsigned char VIA_DXS_MAX_VOLUME ; 
 scalar_t__ VIA_REG_OFS_PLAYBACK_VOLUME_L ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 struct via82xx* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_via8233_dxs_volume_put(struct snd_kcontrol *kcontrol,
				      struct snd_ctl_elem_value *ucontrol)
{
	struct via82xx *chip = snd_kcontrol_chip(kcontrol);
	unsigned int idx = kcontrol->id.subdevice;
	unsigned long port = chip->port + 0x10 * idx;
	unsigned char val;
	int i, change = 0;

	for (i = 0; i < 2; i++) {
		val = ucontrol->value.integer.value[i];
		if (val > VIA_DXS_MAX_VOLUME)
			val = VIA_DXS_MAX_VOLUME;
		val = VIA_DXS_MAX_VOLUME - val;
		change |= val != chip->playback_volume[idx][i];
		if (change) {
			chip->playback_volume[idx][i] = val;
			outb(val, port + VIA_REG_OFS_PLAYBACK_VOLUME_L + i);
		}
	}
	return change;
}