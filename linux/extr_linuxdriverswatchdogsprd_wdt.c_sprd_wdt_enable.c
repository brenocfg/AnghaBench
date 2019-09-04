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
struct sprd_wdt {scalar_t__ base; int /*<<< orphan*/  enable; int /*<<< orphan*/  rtc_enable; } ;

/* Variables and functions */
 scalar_t__ SPRD_WDT_CTRL ; 
 int /*<<< orphan*/  SPRD_WDT_NEW_VER_EN ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  sprd_wdt_lock (scalar_t__) ; 
 int /*<<< orphan*/  sprd_wdt_unlock (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sprd_wdt_enable(struct sprd_wdt *wdt)
{
	u32 val;
	int ret;

	ret = clk_prepare_enable(wdt->enable);
	if (ret)
		return ret;
	ret = clk_prepare_enable(wdt->rtc_enable);
	if (ret) {
		clk_disable_unprepare(wdt->enable);
		return ret;
	}

	sprd_wdt_unlock(wdt->base);
	val = readl_relaxed(wdt->base + SPRD_WDT_CTRL);
	val |= SPRD_WDT_NEW_VER_EN;
	writel_relaxed(val, wdt->base + SPRD_WDT_CTRL);
	sprd_wdt_lock(wdt->base);
	return 0;
}