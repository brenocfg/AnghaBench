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
typedef  unsigned int u32 ;
struct stm32_gpio_bank {int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; scalar_t__ base; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 scalar_t__ STM32_GPIO_TYPER ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static u32 stm32_pconf_get_driving(struct stm32_gpio_bank *bank,
	unsigned int offset)
{
	unsigned long flags;
	u32 val;

	clk_enable(bank->clk);
	spin_lock_irqsave(&bank->lock, flags);

	val = readl_relaxed(bank->base + STM32_GPIO_TYPER);
	val &= BIT(offset);

	spin_unlock_irqrestore(&bank->lock, flags);
	clk_disable(bank->clk);

	return (val >> offset);
}