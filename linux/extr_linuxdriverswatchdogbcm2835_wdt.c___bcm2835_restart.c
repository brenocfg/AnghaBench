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
typedef  int u8 ;
typedef  int u32 ;
struct bcm2835_wdt {scalar_t__ base; } ;

/* Variables and functions */
 int BIT (int) ; 
 int PM_PASSWORD ; 
 scalar_t__ PM_RSTC ; 
 int PM_RSTC_WRCFG_CLR ; 
 int PM_RSTC_WRCFG_FULL_RESET ; 
 scalar_t__ PM_RSTS ; 
 int PM_RSTS_PARTITION_CLR ; 
 scalar_t__ PM_WDOG ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void __bcm2835_restart(struct bcm2835_wdt *wdt, u8 partition)
{
	u32 val, rsts;

	rsts = (partition & BIT(0)) | ((partition & BIT(1)) << 1) |
	       ((partition & BIT(2)) << 2) | ((partition & BIT(3)) << 3) |
	       ((partition & BIT(4)) << 4) | ((partition & BIT(5)) << 5);

	val = readl_relaxed(wdt->base + PM_RSTS);
	val &= PM_RSTS_PARTITION_CLR;
	val |= PM_PASSWORD | rsts;
	writel_relaxed(val, wdt->base + PM_RSTS);

	/* use a timeout of 10 ticks (~150us) */
	writel_relaxed(10 | PM_PASSWORD, wdt->base + PM_WDOG);
	val = readl_relaxed(wdt->base + PM_RSTC);
	val &= PM_RSTC_WRCFG_CLR;
	val |= PM_PASSWORD | PM_RSTC_WRCFG_FULL_RESET;
	writel_relaxed(val, wdt->base + PM_RSTC);

	/* No sleeping, possibly atomic. */
	mdelay(1);
}