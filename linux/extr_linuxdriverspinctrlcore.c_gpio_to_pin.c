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
struct pinctrl_gpio_range {unsigned int base; int* pins; int pin_base; } ;

/* Variables and functions */

__attribute__((used)) static inline int gpio_to_pin(struct pinctrl_gpio_range *range,
				unsigned int gpio)
{
	unsigned int offset = gpio - range->base;
	if (range->pins)
		return range->pins[offset];
	else
		return range->pin_base + offset;
}