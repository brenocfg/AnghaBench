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
struct zx2967_wdt {int dummy; } ;

/* Variables and functions */
 int ZX2967_WDT_START_EN ; 
 int /*<<< orphan*/  ZX2967_WDT_START_REG ; 
 int ZX2967_WDT_VAL_MASK ; 
 int zx2967_wdt_readl (struct zx2967_wdt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zx2967_wdt_writel (struct zx2967_wdt*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void __zx2967_wdt_start(struct zx2967_wdt *wdt)
{
	u32 val;

	val = zx2967_wdt_readl(wdt, ZX2967_WDT_START_REG);
	val |= ZX2967_WDT_START_EN;
	zx2967_wdt_writel(wdt, ZX2967_WDT_START_REG,
			val & ZX2967_WDT_VAL_MASK);
}