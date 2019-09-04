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
 unsigned int ktime_get_seconds () ; 
 unsigned int wdt_expires ; 

__attribute__((used)) static unsigned int xen_wdt_get_timeleft(struct watchdog_device *wdd)
{
	return wdt_expires - ktime_get_seconds();
}