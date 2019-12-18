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
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_ca0106 {int dummy; } ;

/* Variables and functions */
 unsigned int snd_ca0106_ptr_read (struct snd_ca0106*,int,int) ; 
 struct snd_ca0106* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ca0106_volume_get(struct snd_kcontrol *kcontrol,
				 struct snd_ctl_elem_value *ucontrol)
{
        struct snd_ca0106 *emu = snd_kcontrol_chip(kcontrol);
        unsigned int value;
	int channel_id, reg;

	channel_id = (kcontrol->private_value >> 8) & 0xff;
	reg = kcontrol->private_value & 0xff;

        value = snd_ca0106_ptr_read(emu, reg, channel_id);
        ucontrol->value.integer.value[0] = 0xff - ((value >> 24) & 0xff); /* Left */
        ucontrol->value.integer.value[1] = 0xff - ((value >> 16) & 0xff); /* Right */
        return 0;
}