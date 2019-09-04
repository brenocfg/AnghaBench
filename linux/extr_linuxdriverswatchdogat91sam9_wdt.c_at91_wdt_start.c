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
struct watchdog_device {int timeout; } ;
struct at91wdt {scalar_t__ next_heartbeat; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ jiffies ; 
 struct at91wdt* to_wdt (struct watchdog_device*) ; 

__attribute__((used)) static int at91_wdt_start(struct watchdog_device *wdd)
{
	struct at91wdt *wdt = to_wdt(wdd);
	/* calculate when the next userspace timeout will be */
	wdt->next_heartbeat = jiffies + wdd->timeout * HZ;
	return 0;
}