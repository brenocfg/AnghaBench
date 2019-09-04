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
struct TYPE_2__ {int timeout; } ;
struct lpc18xx_wdt_dev {int clk_rate; scalar_t__ base; TYPE_1__ wdt_dev; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPC18XX_WDT_CLK_DIV ; 
 scalar_t__ LPC18XX_WDT_TC ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void __lpc18xx_wdt_set_timeout(struct lpc18xx_wdt_dev *lpc18xx_wdt)
{
	unsigned int val;

	val = DIV_ROUND_UP(lpc18xx_wdt->wdt_dev.timeout * lpc18xx_wdt->clk_rate,
			   LPC18XX_WDT_CLK_DIV);
	writel(val, lpc18xx_wdt->base + LPC18XX_WDT_TC);
}