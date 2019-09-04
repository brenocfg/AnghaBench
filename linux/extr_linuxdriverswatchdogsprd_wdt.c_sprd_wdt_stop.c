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
struct watchdog_device {int dummy; } ;
struct sprd_wdt {scalar_t__ base; } ;

/* Variables and functions */
 int SPRD_WDT_CNT_EN_BIT ; 
 scalar_t__ SPRD_WDT_CTRL ; 
 int SPRD_WDT_INT_EN_BIT ; 
 int SPRD_WDT_RST_EN_BIT ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  sprd_wdt_lock (scalar_t__) ; 
 int /*<<< orphan*/  sprd_wdt_unlock (scalar_t__) ; 
 struct sprd_wdt* to_sprd_wdt (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int sprd_wdt_stop(struct watchdog_device *wdd)
{
	struct sprd_wdt *wdt = to_sprd_wdt(wdd);
	u32 val;

	sprd_wdt_unlock(wdt->base);
	val = readl_relaxed(wdt->base + SPRD_WDT_CTRL);
	val &= ~(SPRD_WDT_CNT_EN_BIT | SPRD_WDT_RST_EN_BIT |
		SPRD_WDT_INT_EN_BIT);
	writel_relaxed(val, wdt->base + SPRD_WDT_CTRL);
	sprd_wdt_lock(wdt->base);
	return 0;
}