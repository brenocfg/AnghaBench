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
struct watchdog_device {TYPE_1__* parent; void* max_timeout; scalar_t__ min_timeout; void* timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct retu_wdt_dev {int /*<<< orphan*/  ping_work; TYPE_1__* dev; struct retu_dev* rdev; } ;
struct retu_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* RETU_WDT_MAX_TIMER ; 
 int WATCHDOG_NOWAYOUT ; 
 struct retu_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 void* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct watchdog_device*) ; 
 int /*<<< orphan*/  retu_wdt_info ; 
 int /*<<< orphan*/  retu_wdt_ops ; 
 int /*<<< orphan*/  retu_wdt_ping (struct watchdog_device*) ; 
 int /*<<< orphan*/  retu_wdt_ping_enable (struct retu_wdt_dev*) ; 
 int /*<<< orphan*/  retu_wdt_ping_work ; 
 int watchdog_register_device (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct retu_wdt_dev*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int) ; 

__attribute__((used)) static int retu_wdt_probe(struct platform_device *pdev)
{
	struct retu_dev *rdev = dev_get_drvdata(pdev->dev.parent);
	bool nowayout = WATCHDOG_NOWAYOUT;
	struct watchdog_device *retu_wdt;
	struct retu_wdt_dev *wdev;
	int ret;

	retu_wdt = devm_kzalloc(&pdev->dev, sizeof(*retu_wdt), GFP_KERNEL);
	if (!retu_wdt)
		return -ENOMEM;

	wdev = devm_kzalloc(&pdev->dev, sizeof(*wdev), GFP_KERNEL);
	if (!wdev)
		return -ENOMEM;

	retu_wdt->info		= &retu_wdt_info;
	retu_wdt->ops		= &retu_wdt_ops;
	retu_wdt->timeout	= RETU_WDT_MAX_TIMER;
	retu_wdt->min_timeout	= 0;
	retu_wdt->max_timeout	= RETU_WDT_MAX_TIMER;
	retu_wdt->parent	= &pdev->dev;

	watchdog_set_drvdata(retu_wdt, wdev);
	watchdog_set_nowayout(retu_wdt, nowayout);

	wdev->rdev		= rdev;
	wdev->dev		= &pdev->dev;

	INIT_DELAYED_WORK(&wdev->ping_work, retu_wdt_ping_work);

	ret = watchdog_register_device(retu_wdt);
	if (ret < 0)
		return ret;

	if (nowayout)
		retu_wdt_ping(retu_wdt);
	else
		retu_wdt_ping_enable(wdev);

	platform_set_drvdata(pdev, retu_wdt);

	return 0;
}