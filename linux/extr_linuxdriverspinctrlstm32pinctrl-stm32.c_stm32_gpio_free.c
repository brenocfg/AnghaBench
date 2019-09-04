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
struct gpio_chip {unsigned int base; } ;

/* Variables and functions */
 int /*<<< orphan*/  pinctrl_gpio_free (unsigned int) ; 

__attribute__((used)) static void stm32_gpio_free(struct gpio_chip *chip, unsigned offset)
{
	pinctrl_gpio_free(chip->base + offset);
}