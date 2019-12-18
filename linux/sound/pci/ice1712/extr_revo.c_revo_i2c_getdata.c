#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snd_ice1712 {int dummy; } ;
struct snd_i2c_bus {struct snd_ice1712* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  VT1724_REVO_I2C_DATA ; 
 scalar_t__ snd_ice1712_gpio_read_bits (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int revo_i2c_getdata(struct snd_i2c_bus *bus, int ack)
{
	struct snd_ice1712 *ice = bus->private_data;
	int bit;

	if (ack)
		udelay(5);
	bit = snd_ice1712_gpio_read_bits(ice, VT1724_REVO_I2C_DATA) ? 1 : 0;
	return bit;
}