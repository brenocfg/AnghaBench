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
struct abx500_pinrange {unsigned int offset; int npins; } ;
struct abx500_pinctrl_soc_data {int gpio_num_ranges; struct abx500_pinrange* gpio_ranges; } ;

/* Variables and functions */

__attribute__((used)) static int abx500_get_gpio_num(struct abx500_pinctrl_soc_data *soc)
{
	unsigned int lowest = 0;
	unsigned int highest = 0;
	unsigned int npins = 0;
	int i;

	/*
	 * Compute number of GPIOs from the last SoC gpio range descriptors
	 * These ranges may include "holes" but the GPIO number space shall
	 * still be homogeneous, so we need to detect and account for any
	 * such holes so that these are included in the number of GPIO pins.
	 */
	for (i = 0; i < soc->gpio_num_ranges; i++) {
		unsigned gstart;
		unsigned gend;
		const struct abx500_pinrange *p;

		p = &soc->gpio_ranges[i];
		gstart = p->offset;
		gend = p->offset + p->npins - 1;

		if (i == 0) {
			/* First iteration, set start values */
			lowest = gstart;
			highest = gend;
		} else {
			if (gstart < lowest)
				lowest = gstart;
			if (gend > highest)
				highest = gend;
		}
	}
	/* this gives the absolute number of pins */
	npins = highest - lowest + 1;
	return npins;
}