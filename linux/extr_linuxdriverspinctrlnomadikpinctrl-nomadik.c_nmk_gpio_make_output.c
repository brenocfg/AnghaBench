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
struct nmk_gpio_chip {int /*<<< orphan*/  clk; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __nmk_gpio_make_output (struct nmk_gpio_chip*,unsigned int,int) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 struct nmk_gpio_chip* gpiochip_get_data (struct gpio_chip*) ; 

__attribute__((used)) static int nmk_gpio_make_output(struct gpio_chip *chip, unsigned offset,
				int val)
{
	struct nmk_gpio_chip *nmk_chip = gpiochip_get_data(chip);

	clk_enable(nmk_chip->clk);

	__nmk_gpio_make_output(nmk_chip, offset, val);

	clk_disable(nmk_chip->clk);

	return 0;
}