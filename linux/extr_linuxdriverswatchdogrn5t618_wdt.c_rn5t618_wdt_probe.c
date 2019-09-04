#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int min_timeout; int max_timeout; int timeout; TYPE_5__* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct rn5t618_wdt {TYPE_1__ wdt_dev; struct rn5t618* rn5t618; } ;
struct rn5t618 {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_5__ dev; } ;
struct TYPE_11__ {int time; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_6__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rn5t618* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct rn5t618_wdt* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rn5t618_wdt*) ; 
 int /*<<< orphan*/  rn5t618_wdt_info ; 
 TYPE_6__* rn5t618_wdt_map ; 
 int /*<<< orphan*/  rn5t618_wdt_ops ; 
 int /*<<< orphan*/  timeout ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct rn5t618_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rn5t618_wdt_probe(struct platform_device *pdev)
{
	struct rn5t618 *rn5t618 = dev_get_drvdata(pdev->dev.parent);
	struct rn5t618_wdt *wdt;
	int min_timeout, max_timeout;

	wdt = devm_kzalloc(&pdev->dev, sizeof(struct rn5t618_wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	min_timeout = rn5t618_wdt_map[0].time;
	max_timeout = rn5t618_wdt_map[ARRAY_SIZE(rn5t618_wdt_map) - 1].time;

	wdt->rn5t618 = rn5t618;
	wdt->wdt_dev.info = &rn5t618_wdt_info;
	wdt->wdt_dev.ops = &rn5t618_wdt_ops;
	wdt->wdt_dev.min_timeout = min_timeout;
	wdt->wdt_dev.max_timeout = max_timeout;
	wdt->wdt_dev.timeout = max_timeout;
	wdt->wdt_dev.parent = &pdev->dev;

	watchdog_set_drvdata(&wdt->wdt_dev, wdt);
	watchdog_init_timeout(&wdt->wdt_dev, timeout, &pdev->dev);
	watchdog_set_nowayout(&wdt->wdt_dev, nowayout);

	platform_set_drvdata(pdev, wdt);

	return watchdog_register_device(&wdt->wdt_dev);
}