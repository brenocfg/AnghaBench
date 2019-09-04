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
struct nmk_gpio_chip {scalar_t__ addr; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ NMK_GPIO_SLPC ; 
 int NUM_BANKS ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 struct nmk_gpio_chip** nmk_gpio_chips ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void nmk_gpio_glitch_slpm_init(unsigned int *slpm)
{
	int i;

	for (i = 0; i < NUM_BANKS; i++) {
		struct nmk_gpio_chip *chip = nmk_gpio_chips[i];
		unsigned int temp = slpm[i];

		if (!chip)
			break;

		clk_enable(chip->clk);

		slpm[i] = readl(chip->addr + NMK_GPIO_SLPC);
		writel(temp, chip->addr + NMK_GPIO_SLPC);
	}
}