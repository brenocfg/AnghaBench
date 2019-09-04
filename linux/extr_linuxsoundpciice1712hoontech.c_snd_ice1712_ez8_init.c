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
struct TYPE_4__ {int /*<<< orphan*/  gpiostate; int /*<<< orphan*/  gpiodir; int /*<<< orphan*/  gpiomask; } ;
struct TYPE_3__ {int /*<<< orphan*/  direction; int /*<<< orphan*/  write_mask; } ;
struct snd_ice1712 {TYPE_2__ eeprom; TYPE_1__ gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE1712_IREG_GPIO_DATA ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_DIRECTION ; 
 int /*<<< orphan*/  ICE1712_IREG_GPIO_WRITE_MASK ; 
 int /*<<< orphan*/  snd_ice1712_write (struct snd_ice1712*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_ice1712_ez8_init(struct snd_ice1712 *ice)
{
	ice->gpio.write_mask = ice->eeprom.gpiomask;
	ice->gpio.direction = ice->eeprom.gpiodir;
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_WRITE_MASK, ice->eeprom.gpiomask);
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_DIRECTION, ice->eeprom.gpiodir);
	snd_ice1712_write(ice, ICE1712_IREG_GPIO_DATA, ice->eeprom.gpiostate);
	return 0;
}