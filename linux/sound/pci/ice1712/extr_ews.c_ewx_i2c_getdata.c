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
 int /*<<< orphan*/  ICE1712_EWX2496_RW ; 
 int /*<<< orphan*/  ICE1712_EWX2496_SERIAL_CLOCK ; 
 int ICE1712_EWX2496_SERIAL_DATA ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_DATA ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_WRITE_MASK ; 
 int snd_ice1712_read (struct snd_ice1712*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ice1712_write (struct snd_ice1712*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ewx_i2c_getdata(struct snd_i2c_bus *bus, int ack)
{
	struct snd_ice1712 *ice = bus->private_data;
	int bit;
	/* set RW pin to low */
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_WRITE_MASK, ~ICE1712_EWX2496_RW);
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA, 0);
	if (ack)
		udelay(5);
	bit = snd_ice1712_read(ice, ICE1712_IREG_GPIO_DATA) & ICE1712_EWX2496_SERIAL_DATA ? 1 : 0;
	/* set RW pin to high */
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA, ICE1712_EWX2496_RW);
	/* reset write mask */
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_WRITE_MASK, ~ICE1712_EWX2496_SERIAL_CLOCK);
	return bit;
}