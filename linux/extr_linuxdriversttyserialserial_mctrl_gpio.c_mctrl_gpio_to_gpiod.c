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
struct mctrl_gpios {struct gpio_desc** gpio; } ;
struct gpio_desc {int dummy; } ;
typedef  enum mctrl_gpio_idx { ____Placeholder_mctrl_gpio_idx } mctrl_gpio_idx ;

/* Variables and functions */

struct gpio_desc *mctrl_gpio_to_gpiod(struct mctrl_gpios *gpios,
				      enum mctrl_gpio_idx gidx)
{
	return gpios->gpio[gidx];
}