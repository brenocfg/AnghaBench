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
struct watchdog_device {unsigned int timeout; } ;

/* Variables and functions */
 scalar_t__ VIA_WDT_COUNT ; 
 unsigned int VIA_WDT_RUNNING ; 
 unsigned int VIA_WDT_TRIGGER ; 
 scalar_t__ WDT_HEARTBEAT ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  timer ; 
 scalar_t__ wdt_mem ; 
 int /*<<< orphan*/  wdt_ping (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int wdt_start(struct watchdog_device *wdd)
{
	unsigned int ctl = readl(wdt_mem);

	writel(wdd->timeout, wdt_mem + VIA_WDT_COUNT);
	writel(ctl | VIA_WDT_RUNNING | VIA_WDT_TRIGGER, wdt_mem);
	wdt_ping(wdd);
	mod_timer(&timer, jiffies + WDT_HEARTBEAT);
	return 0;
}