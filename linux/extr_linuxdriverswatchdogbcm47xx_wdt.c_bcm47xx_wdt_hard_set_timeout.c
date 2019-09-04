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
struct watchdog_device {unsigned int timeout; } ;
struct bcm47xx_wdt {int max_timer_ms; } ;

/* Variables and functions */
 int EINVAL ; 
 struct bcm47xx_wdt* bcm47xx_wdt_get (struct watchdog_device*) ; 
 int /*<<< orphan*/  pr_warn (char*,int,unsigned int) ; 

__attribute__((used)) static int bcm47xx_wdt_hard_set_timeout(struct watchdog_device *wdd,
					unsigned int new_time)
{
	struct bcm47xx_wdt *wdt = bcm47xx_wdt_get(wdd);
	u32 max_timer = wdt->max_timer_ms;

	if (new_time < 1 || new_time > max_timer / 1000) {
		pr_warn("timeout value must be 1<=x<=%d, using %d\n",
			max_timer / 1000, new_time);
		return -EINVAL;
	}

	wdd->timeout = new_time;
	return 0;
}