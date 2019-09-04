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
struct TYPE_2__ {int subvendor; } ;
struct snd_ice1712 {TYPE_1__ eeprom; } ;
struct snd_i2c_bus {struct snd_ice1712* private_data; } ;

/* Variables and functions */
 unsigned char ICE1712_6FIRE_AK4524_CS_MASK ; 
 unsigned char ICE1712_EWX2496_AK4524_CS ; 
 unsigned char ICE1712_EWX2496_RW ; 
#define  ICE1712_SUBDEVICE_DMX6FIRE 129 
#define  ICE1712_SUBDEVICE_EWX2496 128 
 int /*<<< orphan*/  snd_ice1712_gpio_write_bits (struct snd_ice1712*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  snd_ice1712_save_gpio_status (struct snd_ice1712*) ; 

__attribute__((used)) static void ewx_i2c_start(struct snd_i2c_bus *bus)
{
	struct snd_ice1712 *ice = bus->private_data;
	unsigned char mask;

	snd_ice1712_save_gpio_status(ice);
	/* set RW high */
	mask = ICE1712_EWX2496_RW;
	switch (ice->eeprom.subvendor) {
	case ICE1712_SUBDEVICE_EWX2496:
		mask |= ICE1712_EWX2496_AK4524_CS; /* CS high also */
		break;
	case ICE1712_SUBDEVICE_DMX6FIRE:
		mask |= ICE1712_6FIRE_AK4524_CS_MASK; /* CS high also */
		break;
	}
	snd_ice1712_gpio_write_bits(ice, mask, mask);
}