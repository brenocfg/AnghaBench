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
struct watchdog_device {scalar_t__ timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  jz4740_wdt_start (struct watchdog_device*) ; 

__attribute__((used)) static int jz4740_wdt_restart(struct watchdog_device *wdt_dev,
			      unsigned long action, void *data)
{
	wdt_dev->timeout = 0;
	jz4740_wdt_start(wdt_dev);
	return 0;
}