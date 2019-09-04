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
struct nmk_gpio_chip {scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (unsigned int) ; 
 scalar_t__ NMK_GPIO_DATC ; 
 scalar_t__ NMK_GPIO_DATS ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void __nmk_gpio_set_output(struct nmk_gpio_chip *nmk_chip,
				  unsigned offset, int val)
{
	if (val)
		writel(BIT(offset), nmk_chip->addr + NMK_GPIO_DATS);
	else
		writel(BIT(offset), nmk_chip->addr + NMK_GPIO_DATC);
}