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
typedef  int u32 ;
struct bcm2835_pinctrl {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int GPIO_REG_OFFSET (unsigned int) ; 
 int GPIO_REG_SHIFT (unsigned int) ; 
 scalar_t__ GPPUD ; 
 scalar_t__ GPPUDCLK0 ; 
 int /*<<< orphan*/  bcm2835_gpio_wr (struct bcm2835_pinctrl*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void bcm2835_pull_config_set(struct bcm2835_pinctrl *pc,
		unsigned int pin, unsigned int arg)
{
	u32 off, bit;

	off = GPIO_REG_OFFSET(pin);
	bit = GPIO_REG_SHIFT(pin);

	bcm2835_gpio_wr(pc, GPPUD, arg & 3);
	/*
	 * BCM2835 datasheet say to wait 150 cycles, but not of what.
	 * But the VideoCore firmware delay for this operation
	 * based nearly on the same amount of VPU cycles and this clock
	 * runs at 250 MHz.
	 */
	udelay(1);
	bcm2835_gpio_wr(pc, GPPUDCLK0 + (off * 4), BIT(bit));
	udelay(1);
	bcm2835_gpio_wr(pc, GPPUDCLK0 + (off * 4), 0);
}