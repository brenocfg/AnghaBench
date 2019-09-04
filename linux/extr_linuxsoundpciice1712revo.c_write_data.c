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

/* Variables and functions */
 unsigned int VT1724_REVO_CCLK ; 
 unsigned int VT1724_REVO_CDOUT ; 
 int /*<<< orphan*/  snd_ice1712_gpio_write (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void write_data(struct snd_ice1712 *ice, unsigned int gpio,
		       unsigned int data, int idx)
{
	for (; idx >= 0; idx--) {
		/* drop clock */
		gpio &= ~VT1724_REVO_CCLK;
		snd_ice1712_gpio_write(ice, gpio);
		udelay(1);
		/* set data */
		if (data & (1 << idx))
			gpio |= VT1724_REVO_CDOUT;
		else
			gpio &= ~VT1724_REVO_CDOUT;
		snd_ice1712_gpio_write(ice, gpio);
		udelay(1);
		/* raise clock */
		gpio |= VT1724_REVO_CCLK;
		snd_ice1712_gpio_write(ice, gpio);
		udelay(1);
	}
}