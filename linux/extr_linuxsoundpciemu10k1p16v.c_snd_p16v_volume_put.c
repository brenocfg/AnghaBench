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
 int snd_emu10k1_ptr20_read (struct snd_emu10k1*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_emu10k1_ptr20_write (struct snd_emu10k1*,int,int /*<<< orphan*/ ,int) ; 
 struct snd_emu10k1* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_p16v_volume_put(struct snd_kcontrol *kcontrol,
			       struct snd_ctl_elem_value *ucontrol)
{
        struct snd_emu10k1 *emu = snd_kcontrol_chip(kcontrol);
	int high_low = (kcontrol->private_value >> 8) & 0xff;
	int reg = kcontrol->private_value & 0xff;
        u32 value, oval;

	oval = value = snd_emu10k1_ptr20_read(emu, reg, 0);
	if (high_low == 1) {
		value &= 0xffff;
		value |= ((0xff - ucontrol->value.integer.value[0]) << 24) |
			((0xff - ucontrol->value.integer.value[1]) << 16);
	} else {
		value &= 0xffff0000;
		value |= ((0xff - ucontrol->value.integer.value[0]) << 8) |
			((0xff - ucontrol->value.integer.value[1]) );
	}
	if (value != oval) {
		snd_emu10k1_ptr20_write(emu, reg, 0, value);
		return 1;
	}
	return 0;
}