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
typedef  int /*<<< orphan*/  u32 ;
struct dw_wdt {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ WDOG_CONTROL_REG_OFFSET ; 
 int /*<<< orphan*/  WDOG_CONTROL_REG_RESP_MODE_MASK ; 
 int /*<<< orphan*/  WDOG_CONTROL_REG_WDT_EN_MASK ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void dw_wdt_arm_system_reset(struct dw_wdt *dw_wdt)
{
	u32 val = readl(dw_wdt->regs + WDOG_CONTROL_REG_OFFSET);

	/* Disable interrupt mode; always perform system reset. */
	val &= ~WDOG_CONTROL_REG_RESP_MODE_MASK;
	/* Enable watchdog. */
	val |= WDOG_CONTROL_REG_WDT_EN_MASK;
	writel(val, dw_wdt->regs + WDOG_CONTROL_REG_OFFSET);
}