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
typedef  int u32 ;
struct snd_kcontrol {int private_value; } ;
struct snd_emu10k1 {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int snd_emu10k1_ptr20_read (struct snd_emu10k1*,int,int) ; 
 struct snd_emu10k1* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_p16v_volume_get(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
        struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	int high_low = (kcontrol->private_value >> 8) & 0xff;
	int reg = kcontrol->private_value & 0xff;
	u32 value;

	value = snd_emu10k1_ptr20_read(emu, reg, high_low);
	if (high_low) {
		ucontrol->value.integer.value[0] = 0xff - ((value >> 24) & 0xff); /* Left */
		ucontrol->value.integer.value[1] = 0xff - ((value >> 16) & 0xff); /* Right */
	} else {
		ucontrol->value.integer.value[0] = 0xff - ((value >> 8) & 0xff); /* Left */
		ucontrol->value.integer.value[1] = 0xff - ((value >> 0) & 0xff); /* Right */
	}
	return 0;
}