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
typedef  int u32 ;
struct cns3xxx_gpio_chip {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ GPIO_DIR ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 

__attribute__((used)) static inline void
__set_direction(struct cns3xxx_gpio_chip *cchip, unsigned pin, int input)
{
	u32 reg;

	reg = __raw_readl(cchip->base + GPIO_DIR);
	if (input)
		reg &= ~(1 << pin);
	else
		reg |= (1 << pin);
	__raw_writel(reg, cchip->base + GPIO_DIR);
}