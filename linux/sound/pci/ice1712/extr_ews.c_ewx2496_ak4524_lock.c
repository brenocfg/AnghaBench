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
struct snd_akm4xxx {struct snd_ice1712** private_data; } ;

/* Variables and functions */
 unsigned char ICE1712_EWX2496_AK4524_CS ; 
 unsigned char ICE1712_EWX2496_RW ; 
 unsigned char ICE1712_EWX2496_SERIAL_CLOCK ; 
 unsigned char ICE1712_EWX2496_SERIAL_DATA ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_DIRECTION ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_WRITE_MASK ; 
 int /*<<< orphan*/  snd_ice1712_save_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_write (struct snd_ice1712*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void ewx2496_ak4524_lock(struct snd_akm4xxx *ak, int chip)
{
	struct snd_ice1712 *ice = ak->private_data[0];
	unsigned char tmp;
	snd_ice1712_save_gpio_status(ice);
	tmp =  ICE1712_EWX2496_SERIAL_DATA |
		ICE1712_EWX2496_SERIAL_CLOCK |
		ICE1712_EWX2496_AK4524_CS |
		ICE1712_EWX2496_RW;
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_DIRECTION,
			  ice->gpio.direction | tmp);
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_WRITE_MASK, ~tmp);
}