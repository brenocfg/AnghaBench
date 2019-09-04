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
struct pic32_gpio_bank {scalar_t__ reg_base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 scalar_t__ TRIS_REG ; 
 struct pic32_gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int pic32_gpio_get_direction(struct gpio_chip *chip, unsigned offset)
{
	struct pic32_gpio_bank *bank = gpiochip_get_data(chip);

	return !!(readl(bank->reg_base + TRIS_REG) & BIT(offset));
}