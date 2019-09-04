#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {void* timeout; int /*<<< orphan*/ * parent; int /*<<< orphan*/  min_timeout; void* max_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct sunxi_wdt_dev {TYPE_1__ wdt_dev; int /*<<< orphan*/  wdt_base; int /*<<< orphan*/  wdt_regs; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 void* WDT_MAX_TIMEOUT ; 
 int /*<<< orphan*/  WDT_MIN_TIMEOUT ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct sunxi_wdt_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  nowayout ; 
 int /*<<< orphan*/  of_device_get_match_data (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunxi_wdt_info ; 
 int /*<<< orphan*/  sunxi_wdt_ops ; 
 int /*<<< orphan*/  sunxi_wdt_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  timeout ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct sunxi_wdt_dev*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_set_restart_priority (TYPE_1__*,int) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_1__*) ; 

__attribute__((used)) static int sunxi_wdt_probe(struct platform_device *pdev)
{
	struct sunxi_wdt_dev *sunxi_wdt;
	struct resource *res;
	int err;

	sunxi_wdt = devm_kzalloc(&pdev->dev, sizeof(*sunxi_wdt), GFP_KERNEL);
	if (!sunxi_wdt)
		return -EINVAL;

	sunxi_wdt->wdt_regs = of_device_get_match_data(&pdev->dev);
	if (!sunxi_wdt->wdt_regs)
		return -ENODEV;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	sunxi_wdt->wdt_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(sunxi_wdt->wdt_base))
		return PTR_ERR(sunxi_wdt->wdt_base);

	sunxi_wdt->wdt_dev.info = &sunxi_wdt_info;
	sunxi_wdt->wdt_dev.ops = &sunxi_wdt_ops;
	sunxi_wdt->wdt_dev.timeout = WDT_MAX_TIMEOUT;
	sunxi_wdt->wdt_dev.max_timeout = WDT_MAX_TIMEOUT;
	sunxi_wdt->wdt_dev.min_timeout = WDT_MIN_TIMEOUT;
	sunxi_wdt->wdt_dev.parent = &pdev->dev;

	watchdog_init_timeout(&sunxi_wdt->wdt_dev, timeout, &pdev->dev);
	watchdog_set_nowayout(&sunxi_wdt->wdt_dev, nowayout);
	watchdog_set_restart_priority(&sunxi_wdt->wdt_dev, 128);

	watchdog_set_drvdata(&sunxi_wdt->wdt_dev, sunxi_wdt);

	sunxi_wdt_stop(&sunxi_wdt->wdt_dev);

	watchdog_stop_on_reboot(&sunxi_wdt->wdt_dev);
	err = devm_watchdog_register_device(&pdev->dev, &sunxi_wdt->wdt_dev);
	if (unlikely(err))
		return err;

	dev_info(&pdev->dev, "Watchdog enabled (timeout=%d sec, nowayout=%d)",
			sunxi_wdt->wdt_dev.timeout, nowayout);

	return 0;
}