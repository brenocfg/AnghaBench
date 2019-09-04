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
struct TYPE_2__ {unsigned long timeout; } ;
struct pdc_wdt_dev {scalar_t__ base; TYPE_1__ wdt_dev; int /*<<< orphan*/  wdt_clk; } ;

/* Variables and functions */
 scalar_t__ PDC_WDT_CONFIG ; 
 unsigned int PDC_WDT_CONFIG_DELAY_MASK ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int order_base_2 (unsigned long) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void __pdc_wdt_set_timeout(struct pdc_wdt_dev *wdt)
{
	unsigned long clk_rate = clk_get_rate(wdt->wdt_clk);
	unsigned int val;

	val = readl(wdt->base + PDC_WDT_CONFIG) & ~PDC_WDT_CONFIG_DELAY_MASK;
	val |= order_base_2(wdt->wdt_dev.timeout * clk_rate) - 1;
	writel(val, wdt->base + PDC_WDT_CONFIG);
}