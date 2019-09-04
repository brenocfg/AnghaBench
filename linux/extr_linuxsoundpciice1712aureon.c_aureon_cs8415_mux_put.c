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
struct snd_ice1712 {struct aureon_spec* spec; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct aureon_spec {int cs8415_mux; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS8415_CTRL2 ; 
 unsigned short aureon_cs8415_get (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aureon_cs8415_put (struct snd_ice1712*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  snd_ice1712_restore_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_save_gpio_status (struct snd_ice1712*) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int aureon_cs8415_mux_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	struct aureon_spec *spec = ice->spec;
	unsigned short oval, nval;
	int change;

	snd_ice1712_save_gpio_status(ice);
	oval = aureon_cs8415_get(ice, CS8415_CTRL2);
	nval = oval & ~0x07;
	nval |= ucontrol->value.enumerated.item[0] & 7;
	change = (oval != nval);
	if (change)
		aureon_cs8415_put(ice, CS8415_CTRL2, nval);
	snd_ice1712_restore_gpio_status(ice);
	spec->cs8415_mux = ucontrol->value.enumerated.item[0];
	return change;
}