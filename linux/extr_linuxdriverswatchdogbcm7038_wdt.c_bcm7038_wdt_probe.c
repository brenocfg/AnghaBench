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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_3__ {int max_timeout; struct device* parent; int /*<<< orphan*/  timeout; int /*<<< orphan*/  min_timeout; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct bcm7038_watchdog {int rate; int /*<<< orphan*/ * clk; TYPE_1__ wdd; int /*<<< orphan*/ * base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 void* WDT_DEFAULT_RATE ; 
 int /*<<< orphan*/  WDT_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  WDT_MIN_TIMEOUT ; 
 int /*<<< orphan*/  bcm7038_wdt_info ; 
 int /*<<< orphan*/  bcm7038_wdt_ops ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_get_rate (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/ * devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (struct device*,struct resource*) ; 
 struct bcm7038_watchdog* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bcm7038_watchdog*) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct bcm7038_watchdog*) ; 

__attribute__((used)) static int bcm7038_wdt_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct bcm7038_watchdog *wdt;
	struct resource *res;
	int err;

	wdt = devm_kzalloc(dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	platform_set_drvdata(pdev, wdt);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	wdt->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(wdt->base))
		return PTR_ERR(wdt->base);

	wdt->clk = devm_clk_get(dev, NULL);
	/* If unable to get clock, use default frequency */
	if (!IS_ERR(wdt->clk)) {
		err = clk_prepare_enable(wdt->clk);
		if (err)
			return err;
		wdt->rate = clk_get_rate(wdt->clk);
		/* Prevent divide-by-zero exception */
		if (!wdt->rate)
			wdt->rate = WDT_DEFAULT_RATE;
	} else {
		wdt->rate = WDT_DEFAULT_RATE;
		wdt->clk = NULL;
	}

	wdt->wdd.info		= &bcm7038_wdt_info;
	wdt->wdd.ops		= &bcm7038_wdt_ops;
	wdt->wdd.min_timeout	= WDT_MIN_TIMEOUT;
	wdt->wdd.timeout	= WDT_DEFAULT_TIMEOUT;
	wdt->wdd.max_timeout	= 0xffffffff / wdt->rate;
	wdt->wdd.parent		= dev;
	watchdog_set_drvdata(&wdt->wdd, wdt);

	err = watchdog_register_device(&wdt->wdd);
	if (err) {
		dev_err(dev, "Failed to register watchdog device\n");
		clk_disable_unprepare(wdt->clk);
		return err;
	}

	dev_info(dev, "Registered BCM7038 Watchdog\n");

	return 0;
}