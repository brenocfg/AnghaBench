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
struct imx2_wdt_device {int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IMX2_WDT_WICR ; 
 int /*<<< orphan*/  IMX2_WDT_WICR_WTIS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct imx2_wdt_device* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_notify_pretimeout (struct watchdog_device*) ; 

__attribute__((used)) static irqreturn_t imx2_wdt_isr(int irq, void *wdog_arg)
{
	struct watchdog_device *wdog = wdog_arg;
	struct imx2_wdt_device *wdev = watchdog_get_drvdata(wdog);

	regmap_write_bits(wdev->regmap, IMX2_WDT_WICR,
			  IMX2_WDT_WICR_WTIS, IMX2_WDT_WICR_WTIS);

	watchdog_notify_pretimeout(wdog);

	return IRQ_HANDLED;
}