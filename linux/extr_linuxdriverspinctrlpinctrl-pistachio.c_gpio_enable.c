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
struct pistachio_gpio_bank {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_BIT_EN ; 
 int /*<<< orphan*/  gpio_mask_writel (struct pistachio_gpio_bank*,int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static inline void gpio_enable(struct pistachio_gpio_bank *bank,
			       unsigned offset)
{
	gpio_mask_writel(bank, GPIO_BIT_EN, offset, 1);
}