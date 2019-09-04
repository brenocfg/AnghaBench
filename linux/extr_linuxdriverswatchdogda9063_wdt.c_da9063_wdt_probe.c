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
struct watchdog_device {int /*<<< orphan*/  status; TYPE_1__* parent; int /*<<< orphan*/  timeout; int /*<<< orphan*/  min_hw_heartbeat_ms; int /*<<< orphan*/  max_timeout; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct da9063 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9063_RESET_PROTECTION_MS ; 
 int /*<<< orphan*/  DA9063_WDG_TIMEOUT ; 
 int /*<<< orphan*/  DA9063_WDT_MAX_TIMEOUT ; 
 int /*<<< orphan*/  DA9063_WDT_MIN_TIMEOUT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WATCHDOG_NOWAYOUT_INIT_STATUS ; 
 int /*<<< orphan*/  WDOG_HW_RUNNING ; 
 int /*<<< orphan*/  da9063_watchdog_info ; 
 int /*<<< orphan*/  da9063_watchdog_ops ; 
 scalar_t__ da9063_wdt_is_running (struct da9063*) ; 
 int /*<<< orphan*/  da9063_wdt_update_timeout (struct da9063*,int /*<<< orphan*/ ) ; 
 struct da9063* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct watchdog_device* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (TYPE_1__*,struct watchdog_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct da9063*) ; 
 int /*<<< orphan*/  watchdog_set_restart_priority (struct watchdog_device*,int) ; 

__attribute__((used)) static int da9063_wdt_probe(struct platform_device *pdev)
{
	struct da9063 *da9063;
	struct watchdog_device *wdd;

	if (!pdev->dev.parent)
		return -EINVAL;

	da9063 = dev_get_drvdata(pdev->dev.parent);
	if (!da9063)
		return -EINVAL;

	wdd = devm_kzalloc(&pdev->dev, sizeof(*wdd), GFP_KERNEL);
	if (!wdd)
		return -ENOMEM;

	wdd->info = &da9063_watchdog_info;
	wdd->ops = &da9063_watchdog_ops;
	wdd->min_timeout = DA9063_WDT_MIN_TIMEOUT;
	wdd->max_timeout = DA9063_WDT_MAX_TIMEOUT;
	wdd->min_hw_heartbeat_ms = DA9063_RESET_PROTECTION_MS;
	wdd->timeout = DA9063_WDG_TIMEOUT;
	wdd->parent = &pdev->dev;

	wdd->status = WATCHDOG_NOWAYOUT_INIT_STATUS;

	watchdog_set_restart_priority(wdd, 128);

	watchdog_set_drvdata(wdd, da9063);

	/* Change the timeout to the default value if the watchdog is running */
	if (da9063_wdt_is_running(da9063)) {
		da9063_wdt_update_timeout(da9063, DA9063_WDG_TIMEOUT);
		set_bit(WDOG_HW_RUNNING, &wdd->status);
	}

	return devm_watchdog_register_device(&pdev->dev, wdd);
}