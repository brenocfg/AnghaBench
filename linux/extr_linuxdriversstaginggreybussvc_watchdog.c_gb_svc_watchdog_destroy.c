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
struct gb_svc_watchdog {int /*<<< orphan*/  pm_notifier; } ;
struct gb_svc {struct gb_svc_watchdog* watchdog; } ;

/* Variables and functions */
 int /*<<< orphan*/  gb_svc_watchdog_disable (struct gb_svc*) ; 
 int /*<<< orphan*/  kfree (struct gb_svc_watchdog*) ; 
 int /*<<< orphan*/  unregister_pm_notifier (int /*<<< orphan*/ *) ; 

void gb_svc_watchdog_destroy(struct gb_svc *svc)
{
	struct gb_svc_watchdog *watchdog = svc->watchdog;

	if (!watchdog)
		return;

	unregister_pm_notifier(&watchdog->pm_notifier);
	gb_svc_watchdog_disable(svc);
	svc->watchdog = NULL;
	kfree(watchdog);
}