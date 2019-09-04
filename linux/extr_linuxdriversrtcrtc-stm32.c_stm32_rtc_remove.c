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
struct stm32_rtc_registers {int /*<<< orphan*/  cr; } ;
struct stm32_rtc {int /*<<< orphan*/  dbp_mask; int /*<<< orphan*/  dbp_reg; int /*<<< orphan*/  dbp; TYPE_1__* data; int /*<<< orphan*/  pclk; int /*<<< orphan*/  rtc_ck; scalar_t__ base; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {scalar_t__ need_dbp; scalar_t__ has_pclk; struct stm32_rtc_registers regs; } ;

/* Variables and functions */
 unsigned int STM32_RTC_CR_ALRAIE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_clear_wake_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 struct stm32_rtc* platform_get_drvdata (struct platform_device*) ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_rtc_wpr_lock (struct stm32_rtc*) ; 
 int /*<<< orphan*/  stm32_rtc_wpr_unlock (struct stm32_rtc*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static int stm32_rtc_remove(struct platform_device *pdev)
{
	struct stm32_rtc *rtc = platform_get_drvdata(pdev);
	const struct stm32_rtc_registers *regs = &rtc->data->regs;
	unsigned int cr;

	/* Disable interrupts */
	stm32_rtc_wpr_unlock(rtc);
	cr = readl_relaxed(rtc->base + regs->cr);
	cr &= ~STM32_RTC_CR_ALRAIE;
	writel_relaxed(cr, rtc->base + regs->cr);
	stm32_rtc_wpr_lock(rtc);

	clk_disable_unprepare(rtc->rtc_ck);
	if (rtc->data->has_pclk)
		clk_disable_unprepare(rtc->pclk);

	/* Enable backup domain write protection if needed */
	if (rtc->data->need_dbp)
		regmap_update_bits(rtc->dbp, rtc->dbp_reg, rtc->dbp_mask, 0);

	dev_pm_clear_wake_irq(&pdev->dev);
	device_init_wakeup(&pdev->dev, false);

	return 0;
}