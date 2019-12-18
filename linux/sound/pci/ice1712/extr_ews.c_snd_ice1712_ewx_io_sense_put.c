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
struct snd_ice1712 {int dummy; } ;
struct TYPE_4__ {scalar_t__* item; } ;
struct TYPE_3__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_DATA ; 
 int snd_ice1712_read (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ice1712_restore_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_save_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_write (struct snd_ice1712*,int /*<<< orphan*/ ,int) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int snd_ice1712_ewx_io_sense_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	unsigned char mask = kcontrol->private_value & 0xff;
	int val, nval;

	if (kcontrol->private_value & (1 << 31))
		return -EPERM;
	nval = ucontrol->value.enumerated.item[0] ? mask : 0;
	snd_ice1712_save_gpio_status(ice);
	val = snd_ice1712_read(ice, ICE1712_IREG_GPIO_DATA);
	nval |= val & ~mask;
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA, nval);
	snd_ice1712_restore_gpio_status(ice);
	return val != nval;
}