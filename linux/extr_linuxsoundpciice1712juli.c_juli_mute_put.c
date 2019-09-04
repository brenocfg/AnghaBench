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
struct snd_kcontrol {unsigned int private_value; } ;
struct TYPE_6__ {unsigned int (* get_data ) (struct snd_ice1712*) ;int /*<<< orphan*/  (* set_data ) (struct snd_ice1712*,unsigned int) ;} ;
struct snd_ice1712 {TYPE_3__ gpio; int /*<<< orphan*/  akm; } ;
struct TYPE_4__ {scalar_t__* value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 unsigned int GPIO_MUTE_CONTROL ; 
 int /*<<< orphan*/  snd_akm4xxx_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned int stub1 (struct snd_ice1712*) ; 
 int /*<<< orphan*/  stub2 (struct snd_ice1712*,unsigned int) ; 

__attribute__((used)) static int juli_mute_put(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	unsigned int old_gpio, new_gpio;
	old_gpio = ice->gpio.get_data(ice);
	if (ucontrol->value.integer.value[0]) {
		/* unmute */
		if (kcontrol->private_value == GPIO_MUTE_CONTROL) {
			/* 0 = signal on */
			new_gpio = old_gpio & ~GPIO_MUTE_CONTROL;
			/* un-smuting DAC */
			snd_akm4xxx_write(ice->akm, 0, 0x01, 0x01);
		} else
			/* 1 = signal on */
			new_gpio =  old_gpio |
				(unsigned int) kcontrol->private_value;
	} else {
		/* mute */
		if (kcontrol->private_value == GPIO_MUTE_CONTROL) {
			/* 1 = signal off */
			new_gpio = old_gpio | GPIO_MUTE_CONTROL;
			/* smuting DAC */
			snd_akm4xxx_write(ice->akm, 0, 0x01, 0x03);
		} else
			/* 0 = signal off */
			new_gpio =  old_gpio &
				~((unsigned int) kcontrol->private_value);
	}
	/* dev_dbg(ice->card->dev,
		"JULI - mute/unmute: control_value: 0x%x, old_gpio: 0x%x, "
		"new_gpio 0x%x\n",
		(unsigned int)ucontrol->value.integer.value[0], old_gpio,
		new_gpio); */
	if (old_gpio != new_gpio) {
		ice->gpio.set_data(ice, new_gpio);
		return 1;
	}
	/* no change */
	return 0;
}