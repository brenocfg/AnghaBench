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
struct TYPE_3__ {unsigned char direction; } ;
struct snd_ice1712 {TYPE_1__ gpio; TYPE_2__* card; } ;
struct snd_akm4xxx {struct snd_ice1712** private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned char ICE1712_EWS88_RW ; 
 unsigned char ICE1712_EWS88_SERIAL_CLOCK ; 
 unsigned char ICE1712_EWS88_SERIAL_DATA ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_DIRECTION ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_WRITE_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ snd_ice1712_ews88mt_chip_select (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  snd_ice1712_save_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_write (struct snd_ice1712*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void ews88mt_ak4524_lock(struct snd_akm4xxx *ak, int chip)
{
	struct snd_ice1712 *ice = ak->private_data[0];
	unsigned char tmp;
	/* assert AK4524 CS */
	if (snd_ice1712_ews88mt_chip_select(ice, ~(1 << chip) & 0x0f) < 0)
		dev_err(ice->card->dev, "fatal error (ews88mt chip select)\n");
	snd_ice1712_save_gpio_status(ice);
	tmp = ICE1712_EWS88_SERIAL_DATA |
		ICE1712_EWS88_SERIAL_CLOCK |
		ICE1712_EWS88_RW;
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_DIRECTION,
			  ice->gpio.direction | tmp);
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_WRITE_MASK, ~tmp);
}