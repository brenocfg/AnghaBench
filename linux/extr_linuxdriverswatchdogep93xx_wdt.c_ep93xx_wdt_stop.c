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
struct watchdog_device {int dummy; } ;
struct ep93xx_wdt_priv {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ EP93XX_WATCHDOG ; 
 struct ep93xx_wdt_priv* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ep93xx_wdt_stop(struct watchdog_device *wdd)
{
	struct ep93xx_wdt_priv *priv = watchdog_get_drvdata(wdd);

	writel(0xaa55, priv->mmio + EP93XX_WATCHDOG);

	return 0;
}