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
struct sx150x_pinctrl {int dummy; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __sx150x_gpio_set (struct sx150x_pinctrl*,unsigned int,int) ; 
 struct sx150x_pinctrl* gpiochip_get_data (struct gpio_chip*) ; 
 int /*<<< orphan*/  sx150x_gpio_oscio_set (struct sx150x_pinctrl*,int) ; 
 scalar_t__ sx150x_pin_is_oscio (struct sx150x_pinctrl*,unsigned int) ; 

__attribute__((used)) static void sx150x_gpio_set(struct gpio_chip *chip, unsigned int offset,
			    int value)
{
	struct sx150x_pinctrl *pctl = gpiochip_get_data(chip);

	if (sx150x_pin_is_oscio(pctl, offset))
		sx150x_gpio_oscio_set(pctl, value);
	else
		__sx150x_gpio_set(pctl, offset, value);

}