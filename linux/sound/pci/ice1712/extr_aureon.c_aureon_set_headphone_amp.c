#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ subvendor; } ;
struct snd_ice1712 {TYPE_1__ eeprom; } ;

/* Variables and functions */
 unsigned int AUREON_HP_SEL ; 
 unsigned int PRODIGY_HP_SEL ; 
 scalar_t__ VT1724_SUBDEVICE_PRODIGY71LT ; 
 scalar_t__ VT1724_SUBDEVICE_PRODIGY71XT ; 
 unsigned int snd_ice1712_gpio_read (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_write (struct snd_ice1712*,unsigned int) ; 

__attribute__((used)) static int aureon_set_headphone_amp(struct snd_ice1712 *ice, int enable)
{
	unsigned int tmp, tmp2;

	tmp2 = tmp = snd_ice1712_gpio_read(ice);
	if (enable)
		if (ice->eeprom.subvendor != VT1724_SUBDEVICE_PRODIGY71LT &&
		    ice->eeprom.subvendor != VT1724_SUBDEVICE_PRODIGY71XT)
			tmp |= AUREON_HP_SEL;
		else
			tmp |= PRODIGY_HP_SEL;
	else
		if (ice->eeprom.subvendor != VT1724_SUBDEVICE_PRODIGY71LT &&
		    ice->eeprom.subvendor != VT1724_SUBDEVICE_PRODIGY71XT)
			tmp &= ~AUREON_HP_SEL;
		else
			tmp &= ~PRODIGY_HP_SEL;
	if (tmp != tmp2) {
		snd_ice1712_gpio_write(ice, tmp);
		return 1;
	}
	return 0;
}