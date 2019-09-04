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
 unsigned int VT1724_REVO_CS0 ; 
 unsigned int VT1724_REVO_CS3 ; 
 unsigned int snd_ice1712_gpio_read (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_write (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  snd_ice1712_save_gpio_status (struct snd_ice1712*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static unsigned int ap192_4wire_start(struct snd_ice1712 *ice)
{
	unsigned int tmp;

	snd_ice1712_save_gpio_status(ice);
	tmp = snd_ice1712_gpio_read(ice);
	tmp |= VT1724_REVO_CCLK; /* high at init */
	tmp |= VT1724_REVO_CS0;
	tmp &= ~VT1724_REVO_CS3;
	snd_ice1712_gpio_write(ice, tmp);
	udelay(1);
	return tmp;
}