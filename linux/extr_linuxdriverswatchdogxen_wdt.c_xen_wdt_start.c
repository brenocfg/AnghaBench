#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  time64_t ;
struct watchdog_device {int dummy; } ;
struct TYPE_3__ {int id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EBUSY ; 
 int HYPERVISOR_sched_op (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  SCHEDOP_watchdog ; 
 int /*<<< orphan*/  set_timeout (struct watchdog_device*) ; 
 TYPE_1__ wdt ; 
 int /*<<< orphan*/  wdt_expires ; 

__attribute__((used)) static int xen_wdt_start(struct watchdog_device *wdd)
{
	time64_t expires;
	int err;

	expires = set_timeout(wdd);
	if (!wdt.id)
		err = HYPERVISOR_sched_op(SCHEDOP_watchdog, &wdt);
	else
		err = -EBUSY;
	if (err > 0) {
		wdt.id = err;
		wdt_expires = expires;
		err = 0;
	} else
		BUG_ON(!err);

	return err;
}