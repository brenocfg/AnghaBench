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
struct watchdog_device {int timeout; int min_timeout; int max_timeout; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct jz4740_wdt_drvdata {struct watchdog_device wdt; int /*<<< orphan*/  rtc_clk; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int DEFAULT_HEARTBEAT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_HEARTBEAT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct jz4740_wdt_drvdata* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (int /*<<< orphan*/ *,struct watchdog_device*) ; 
 int heartbeat ; 
 int /*<<< orphan*/  jz4740_wdt_info ; 
 int /*<<< orphan*/  jz4740_wdt_ops ; 
 int /*<<< orphan*/  nowayout ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct jz4740_wdt_drvdata*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct jz4740_wdt_drvdata*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jz4740_wdt_probe(struct platform_device *pdev)
{
	struct jz4740_wdt_drvdata *drvdata;
	struct watchdog_device *jz4740_wdt;
	struct resource	*res;
	int ret;

	drvdata = devm_kzalloc(&pdev->dev, sizeof(struct jz4740_wdt_drvdata),
			       GFP_KERNEL);
	if (!drvdata)
		return -ENOMEM;

	if (heartbeat < 1 || heartbeat > MAX_HEARTBEAT)
		heartbeat = DEFAULT_HEARTBEAT;

	jz4740_wdt = &drvdata->wdt;
	jz4740_wdt->info = &jz4740_wdt_info;
	jz4740_wdt->ops = &jz4740_wdt_ops;
	jz4740_wdt->timeout = heartbeat;
	jz4740_wdt->min_timeout = 1;
	jz4740_wdt->max_timeout = MAX_HEARTBEAT;
	jz4740_wdt->parent = &pdev->dev;
	watchdog_set_nowayout(jz4740_wdt, nowayout);
	watchdog_set_drvdata(jz4740_wdt, drvdata);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	drvdata->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(drvdata->base))
		return PTR_ERR(drvdata->base);

	drvdata->rtc_clk = devm_clk_get(&pdev->dev, "rtc");
	if (IS_ERR(drvdata->rtc_clk)) {
		dev_err(&pdev->dev, "cannot find RTC clock\n");
		return PTR_ERR(drvdata->rtc_clk);
	}

	ret = devm_watchdog_register_device(&pdev->dev, &drvdata->wdt);
	if (ret < 0)
		return ret;

	platform_set_drvdata(pdev, drvdata);

	return 0;
}