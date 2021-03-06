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
struct snd_ice1712 {int dummy; } ;
struct TYPE_3__ {int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 scalar_t__ WM_ADC_GAIN ; 
 int /*<<< orphan*/  snd_ice1712_restore_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_save_gpio_status (struct snd_ice1712*) ; 
 struct snd_ice1712* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 unsigned short wm_get (struct snd_ice1712*,scalar_t__) ; 
 int /*<<< orphan*/  wm_put (struct snd_ice1712*,scalar_t__,unsigned short) ; 

__attribute__((used)) static int wm_adc_mute_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_ice1712 *ice = snd_kcontrol_chip(kcontrol);
	unsigned short new, old;
	int i, change = 0;

	snd_ice1712_save_gpio_status(ice);
	for (i = 0; i < 2; i++) {
		old = wm_get(ice, WM_ADC_GAIN + i);
		new = (~ucontrol->value.integer.value[i]<<5&0x20) | (old&~0x20);
		if (new != old) {
			wm_put(ice, WM_ADC_GAIN + i, new);
			change = 1;
		}
	}
	snd_ice1712_restore_gpio_status(ice);

	return change;
}