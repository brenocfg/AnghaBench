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
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct emu10k1x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROUTING ; 
 int /*<<< orphan*/  SPDIF_SELECT ; 
 int /*<<< orphan*/  snd_emu10k1x_gpio_write (struct emu10k1x*,int) ; 
 int /*<<< orphan*/  snd_emu10k1x_ptr_write (struct emu10k1x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct emu10k1x* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_emu10k1x_shared_spdif_put(struct snd_kcontrol *kcontrol,
					 struct snd_ctl_elem_value *ucontrol)
{
	struct emu10k1x *emu = snd_kcontrol_chip(kcontrol);
	unsigned int val;

	val = ucontrol->value.integer.value[0] ;

	if (val) {
		// enable spdif output
		snd_emu10k1x_ptr_write(emu, SPDIF_SELECT, 0, 0x000);
		snd_emu10k1x_ptr_write(emu, ROUTING, 0, 0x700);
		snd_emu10k1x_gpio_write(emu, 0x1000);
	} else {
		// disable spdif output
		snd_emu10k1x_ptr_write(emu, SPDIF_SELECT, 0, 0x700);
		snd_emu10k1x_ptr_write(emu, ROUTING, 0, 0x1003F);
		snd_emu10k1x_gpio_write(emu, 0x1080);
	}
	return 0;
}