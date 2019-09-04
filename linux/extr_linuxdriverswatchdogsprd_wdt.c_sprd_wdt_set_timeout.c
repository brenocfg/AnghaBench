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
typedef  int /*<<< orphan*/  u32 ;
struct watchdog_device {int /*<<< orphan*/  pretimeout; int /*<<< orphan*/  timeout; } ;
struct sprd_wdt {int dummy; } ;

/* Variables and functions */
 int sprd_wdt_load_value (struct sprd_wdt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sprd_wdt* to_sprd_wdt (struct watchdog_device*) ; 

__attribute__((used)) static int sprd_wdt_set_timeout(struct watchdog_device *wdd,
				u32 timeout)
{
	struct sprd_wdt *wdt = to_sprd_wdt(wdd);

	if (timeout == wdd->timeout)
		return 0;

	wdd->timeout = timeout;

	return sprd_wdt_load_value(wdt, timeout, wdd->pretimeout);
}