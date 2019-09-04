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
struct TYPE_2__ {unsigned char direction; } ;
struct snd_ice1712 {TYPE_1__ gpio; } ;
struct snd_i2c_bus {struct snd_ice1712* private_data; } ;

/* Variables and functions */
 unsigned char ICE1712_EWX2496_SERIAL_CLOCK ; 
 unsigned char ICE1712_EWX2496_SERIAL_DATA ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_DIRECTION ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_WRITE_MASK ; 
 int /*<<< orphan*/  snd_ice1712_write (struct snd_ice1712*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void ewx_i2c_direction(struct snd_i2c_bus *bus, int clock, int data)
{
	struct snd_ice1712 *ice = bus->private_data;
	unsigned char mask = 0;

	if (clock)
		mask |= ICE1712_EWX2496_SERIAL_CLOCK; /* write SCL */
	if (data)
		mask |= ICE1712_EWX2496_SERIAL_DATA; /* write SDA */
	ice->gpio.direction &= ~(ICE1712_EWX2496_SERIAL_CLOCK|ICE1712_EWX2496_SERIAL_DATA);
	ice->gpio.direction |= mask;
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_DIRECTION, ice->gpio.direction);
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_WRITE_MASK, ~mask);
}