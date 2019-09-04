#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sched_watchdog {int /*<<< orphan*/  id; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOSYS ; 
 int HYPERVISOR_sched_op (int /*<<< orphan*/ ,struct sched_watchdog*) ; 
 int /*<<< orphan*/  SCHEDOP_watchdog ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int devm_watchdog_register_device (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  timeout ; 
 scalar_t__ watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_stop_on_unregister (TYPE_1__*) ; 
 TYPE_1__ xen_wdt_dev ; 

__attribute__((used)) static int xen_wdt_probe(struct platform_device *pdev)
{
	struct sched_watchdog wd = { .id = ~0 };
	int ret = HYPERVISOR_sched_op(SCHEDOP_watchdog, &wd);

	if (ret == -ENOSYS) {
		dev_err(&pdev->dev, "watchdog not supported by hypervisor\n");
		return -ENODEV;
	}

	if (ret != -EINVAL) {
		dev_err(&pdev->dev, "unexpected hypervisor error (%d)\n", ret);
		return -ENODEV;
	}

	if (watchdog_init_timeout(&xen_wdt_dev, timeout, NULL))
		dev_info(&pdev->dev, "timeout value invalid, using %d\n",
			xen_wdt_dev.timeout);
	watchdog_set_nowayout(&xen_wdt_dev, nowayout);
	watchdog_stop_on_reboot(&xen_wdt_dev);
	watchdog_stop_on_unregister(&xen_wdt_dev);

	ret = devm_watchdog_register_device(&pdev->dev, &xen_wdt_dev);
	if (ret) {
		dev_err(&pdev->dev, "cannot register watchdog device (%d)\n",
			ret);
		return ret;
	}

	dev_info(&pdev->dev, "initialized (timeout=%ds, nowayout=%d)\n",
		xen_wdt_dev.timeout, nowayout);

	return 0;
}