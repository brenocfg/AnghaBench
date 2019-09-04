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
struct watchdog_device {int timeout; } ;
struct ftwdt010_wdt {scalar_t__ base; scalar_t__ has_irq; } ;

/* Variables and functions */
 scalar_t__ FTWDT010_WDCR ; 
 scalar_t__ FTWDT010_WDLOAD ; 
 scalar_t__ FTWDT010_WDRESTART ; 
 int WDCR_CLOCK_5MHZ ; 
 int WDCR_ENABLE ; 
 int WDCR_SYS_RST ; 
 int WDCR_WDINTR ; 
 int WDRESTART_MAGIC ; 
 int WDT_CLOCK ; 
 struct ftwdt010_wdt* to_ftwdt010_wdt (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ftwdt010_wdt_start(struct watchdog_device *wdd)
{
	struct ftwdt010_wdt *gwdt = to_ftwdt010_wdt(wdd);
	u32 enable;

	writel(wdd->timeout * WDT_CLOCK, gwdt->base + FTWDT010_WDLOAD);
	writel(WDRESTART_MAGIC, gwdt->base + FTWDT010_WDRESTART);
	/* set clock before enabling */
	enable = WDCR_CLOCK_5MHZ | WDCR_SYS_RST;
	writel(enable, gwdt->base + FTWDT010_WDCR);
	if (gwdt->has_irq)
		enable |= WDCR_WDINTR;
	enable |= WDCR_ENABLE;
	writel(enable, gwdt->base + FTWDT010_WDCR);

	return 0;
}