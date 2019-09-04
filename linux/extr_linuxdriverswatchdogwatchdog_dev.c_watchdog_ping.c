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
struct watchdog_device {struct watchdog_core_data* wd_data; } ;
struct watchdog_core_data {int /*<<< orphan*/  last_keepalive; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  _WDOG_KEEPALIVE ; 
 int __watchdog_ping (struct watchdog_device*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_active (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_hw_running (struct watchdog_device*) ; 

__attribute__((used)) static int watchdog_ping(struct watchdog_device *wdd)
{
	struct watchdog_core_data *wd_data = wdd->wd_data;

	if (!watchdog_active(wdd) && !watchdog_hw_running(wdd))
		return 0;

	set_bit(_WDOG_KEEPALIVE, &wd_data->status);

	wd_data->last_keepalive = ktime_get();
	return __watchdog_ping(wdd);
}