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

/* Variables and functions */

__attribute__((used)) static int uniphier_pxs3_get_gpio_muxval(unsigned int pin,
					 unsigned int gpio_offset)
{
	if (gpio_offset >= 120 && gpio_offset <= 143) {	/* XIRQx */
		if (pin >= 219 && pin <= 234)
			return 0;

		return 14;
	}

	return 15;
}