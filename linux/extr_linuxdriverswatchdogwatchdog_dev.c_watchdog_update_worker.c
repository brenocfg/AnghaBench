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
struct watchdog_core_data {int /*<<< orphan*/  timer; } ;
typedef  scalar_t__ ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ watchdog_need_worker (struct watchdog_device*) ; 
 scalar_t__ watchdog_next_keepalive (struct watchdog_device*) ; 

__attribute__((used)) static inline void watchdog_update_worker(struct watchdog_device *wdd)
{
	struct watchdog_core_data *wd_data = wdd->wd_data;

	if (watchdog_need_worker(wdd)) {
		ktime_t t = watchdog_next_keepalive(wdd);

		if (t > 0)
			hrtimer_start(&wd_data->timer, t, HRTIMER_MODE_REL);
	} else {
		hrtimer_cancel(&wd_data->timer);
	}
}