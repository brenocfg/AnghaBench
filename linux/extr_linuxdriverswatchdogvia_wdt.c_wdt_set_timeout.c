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
 scalar_t__ wdt_mem ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int wdt_set_timeout(struct watchdog_device *wdd,
			   unsigned int new_timeout)
{
	writel(new_timeout, wdt_mem + VIA_WDT_COUNT);
	wdd->timeout = new_timeout;
	return 0;
}