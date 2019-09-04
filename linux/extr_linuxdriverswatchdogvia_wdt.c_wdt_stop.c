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

/* Variables and functions */
 unsigned int VIA_WDT_RUNNING ; 
 unsigned int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wdt_mem ; 
 int /*<<< orphan*/  writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wdt_stop(struct watchdog_device *wdd)
{
	unsigned int ctl = readl(wdt_mem);

	writel(ctl & ~VIA_WDT_RUNNING, wdt_mem);
	return 0;
}