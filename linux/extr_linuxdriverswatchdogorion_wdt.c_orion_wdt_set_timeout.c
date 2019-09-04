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

__attribute__((used)) static int orion_wdt_set_timeout(struct watchdog_device *wdt_dev,
				 unsigned int timeout)
{
	wdt_dev->timeout = timeout;
	return 0;
}