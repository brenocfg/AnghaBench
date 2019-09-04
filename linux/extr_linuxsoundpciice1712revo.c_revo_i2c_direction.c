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
struct TYPE_2__ {unsigned int direction; } ;
struct snd_ice1712 {TYPE_1__ gpio; } ;
struct snd_i2c_bus {struct snd_ice1712* private_data; } ;

/* Variables and functions */
 unsigned int VT1724_REVO_I2C_CLOCK ; 
 unsigned int VT1724_REVO_I2C_DATA ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_dir (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_mask (struct snd_ice1712*,unsigned int) ; 

__attribute__((used)) static void revo_i2c_direction(struct snd_i2c_bus *bus, int clock, int data)
{
	struct snd_ice1712 *ice = bus->private_data;
	unsigned int mask, val;

	val = 0;
	if (clock)
		val |= VT1724_REVO_I2C_CLOCK;	/* write SCL */
	if (data)
		val |= VT1724_REVO_I2C_DATA;	/* write SDA */
	mask = VT1724_REVO_I2C_CLOCK | VT1724_REVO_I2C_DATA;
	ice->gpio.direction &= ~mask;
	ice->gpio.direction |= val;
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction);
	snd_ice1712_gpio_set_mask(ice, ~mask);
}