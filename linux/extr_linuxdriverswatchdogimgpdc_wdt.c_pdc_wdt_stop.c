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
struct pdc_wdt_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ PDC_WDT_CONFIG ; 
 unsigned int PDC_WDT_CONFIG_ENABLE ; 
 int /*<<< orphan*/  pdc_wdt_keepalive (struct watchdog_device*) ; 
 unsigned int readl (scalar_t__) ; 
 struct pdc_wdt_dev* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int pdc_wdt_stop(struct watchdog_device *wdt_dev)
{
	unsigned int val;
	struct pdc_wdt_dev *wdt = watchdog_get_drvdata(wdt_dev);

	val = readl(wdt->base + PDC_WDT_CONFIG);
	val &= ~PDC_WDT_CONFIG_ENABLE;
	writel(val, wdt->base + PDC_WDT_CONFIG);

	/* Must tickle to finish the stop */
	pdc_wdt_keepalive(wdt_dev);

	return 0;
}