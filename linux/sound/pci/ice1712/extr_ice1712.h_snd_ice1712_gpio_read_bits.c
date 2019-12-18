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

/* Variables and functions */
 unsigned int snd_ice1712_gpio_read (struct snd_ice1712*) ; 
 int /*<<< orphan*/  snd_ice1712_gpio_set_dir (struct snd_ice1712*,unsigned int) ; 

__attribute__((used)) static inline int snd_ice1712_gpio_read_bits(struct snd_ice1712 *ice,
					      unsigned int mask)
{
	ice->gpio.direction &= ~mask;
	snd_ice1712_gpio_set_dir(ice, ice->gpio.direction);
	return  snd_ice1712_gpio_read(ice) & mask;
}