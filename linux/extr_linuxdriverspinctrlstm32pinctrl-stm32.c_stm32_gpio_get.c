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
struct stm32_gpio_bank {int /*<<< orphan*/  clk; scalar_t__ base; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int BIT (unsigned int) ; 
 scalar_t__ STM32_GPIO_IDR ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 struct stm32_gpio_bank* gpiochip_get_data (struct gpio_chip*) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int stm32_gpio_get(struct gpio_chip *chip, unsigned offset)
{
	struct stm32_gpio_bank *bank = gpiochip_get_data(chip);
	int ret;

	clk_enable(bank->clk);

	ret = !!(readl_relaxed(bank->base + STM32_GPIO_IDR) & BIT(offset));

	clk_disable(bank->clk);

	return ret;
}