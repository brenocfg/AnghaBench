#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct watchdog_device {int /*<<< orphan*/  status; TYPE_1__* ops; struct watchdog_core_data* wd_data; } ;
struct watchdog_core_data {int /*<<< orphan*/  last_keepalive; int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {int (* ping ) (struct watchdog_device*) ;int (* start ) (struct watchdog_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WDOG_ACTIVE ; 
 int /*<<< orphan*/  _WDOG_KEEPALIVE ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct watchdog_device*) ; 
 int stub2 (struct watchdog_device*) ; 
 scalar_t__ watchdog_active (struct watchdog_device*) ; 
 scalar_t__ watchdog_hw_running (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_update_worker (struct watchdog_device*) ; 

__attribute__((used)) static int watchdog_start(struct watchdog_device *wdd)
{
	struct watchdog_core_data *wd_data = wdd->wd_data;
	ktime_t started_at;
	int err;

	if (watchdog_active(wdd))
		return 0;

	set_bit(_WDOG_KEEPALIVE, &wd_data->status);

	started_at = ktime_get();
	if (watchdog_hw_running(wdd) && wdd->ops->ping)
		err = wdd->ops->ping(wdd);
	else
		err = wdd->ops->start(wdd);
	if (err == 0) {
		set_bit(WDOG_ACTIVE, &wdd->status);
		wd_data->last_keepalive = started_at;
		watchdog_update_worker(wdd);
	}

	return err;
}