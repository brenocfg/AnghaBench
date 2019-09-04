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
struct sprd_wdt {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SPRD_WDT_CNT_HIGH ; 
 int SPRD_WDT_CNT_HIGH_SHIFT ; 
 scalar_t__ SPRD_WDT_CNT_LOW ; 
 int SPRD_WDT_LOW_VALUE_MASK ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static u32 sprd_wdt_get_cnt_value(struct sprd_wdt *wdt)
{
	u32 val;

	val = readl_relaxed(wdt->base + SPRD_WDT_CNT_HIGH) <<
		SPRD_WDT_CNT_HIGH_SHIFT;
	val |= readl_relaxed(wdt->base + SPRD_WDT_CNT_LOW) &
		SPRD_WDT_LOW_VALUE_MASK;

	return val;
}