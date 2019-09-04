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
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_pin_set_value (int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  gpiochip_get_data (struct gpio_chip*) ; 
 int pinctrl_gpio_direction_output (unsigned int) ; 

__attribute__((used)) static int gpio_pin_direction_output(struct gpio_chip *gc, unsigned offset,
				    int value)
{
	gpio_pin_set_value(gpiochip_get_data(gc), offset, value);

	return pinctrl_gpio_direction_output(offset);
}