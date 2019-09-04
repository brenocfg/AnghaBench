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
struct TYPE_3__ {int /*<<< orphan*/  notifier_call; } ;
struct gb_svc_watchdog {int enabled; TYPE_1__ pm_notifier; int /*<<< orphan*/  work; struct gb_svc* svc; } ;
struct gb_svc {struct gb_svc_watchdog* watchdog; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  do_work ; 
 int gb_svc_watchdog_enable (struct gb_svc*) ; 
 int /*<<< orphan*/  kfree (struct gb_svc_watchdog*) ; 
 struct gb_svc_watchdog* kmalloc (int,int /*<<< orphan*/ ) ; 
 int register_pm_notifier (TYPE_1__*) ; 
 int /*<<< orphan*/  svc_watchdog_pm_notifier ; 
 int /*<<< orphan*/  unregister_pm_notifier (TYPE_1__*) ; 

int gb_svc_watchdog_create(struct gb_svc *svc)
{
	struct gb_svc_watchdog *watchdog;
	int retval;

	if (svc->watchdog)
		return 0;

	watchdog = kmalloc(sizeof(*watchdog), GFP_KERNEL);
	if (!watchdog)
		return -ENOMEM;

	watchdog->enabled = false;
	watchdog->svc = svc;
	INIT_DELAYED_WORK(&watchdog->work, do_work);
	svc->watchdog = watchdog;

	watchdog->pm_notifier.notifier_call = svc_watchdog_pm_notifier;
	retval = register_pm_notifier(&watchdog->pm_notifier);
	if (retval) {
		dev_err(&svc->dev, "error registering pm notifier(%d)\n",
			retval);
		goto svc_watchdog_create_err;
	}

	retval = gb_svc_watchdog_enable(svc);
	if (retval) {
		dev_err(&svc->dev, "error enabling watchdog (%d)\n", retval);
		unregister_pm_notifier(&watchdog->pm_notifier);
		goto svc_watchdog_create_err;
	}
	return retval;

svc_watchdog_create_err:
	svc->watchdog = NULL;
	kfree(watchdog);

	return retval;
}