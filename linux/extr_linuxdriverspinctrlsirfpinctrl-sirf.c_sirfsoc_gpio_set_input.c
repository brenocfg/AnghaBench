#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned int regs; } ;
struct sirfsoc_gpio_chip {TYPE_1__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIRFSOC_GPIO_CTL_OUT_EN_MASK ; 
 int /*<<< orphan*/  readl (unsigned int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void sirfsoc_gpio_set_input(struct sirfsoc_gpio_chip *sgpio,
					  unsigned ctrl_offset)
{
	u32 val;

	val = readl(sgpio->chip.regs + ctrl_offset);
	val &= ~SIRFSOC_GPIO_CTL_OUT_EN_MASK;
	writel(val, sgpio->chip.regs + ctrl_offset);
}