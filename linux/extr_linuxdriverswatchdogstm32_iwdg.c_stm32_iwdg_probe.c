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
struct watchdog_device {int min_timeout; int max_hw_heartbeat_ms; int /*<<< orphan*/ * parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct stm32_iwdg {int rate; int /*<<< orphan*/  clk_pclk; int /*<<< orphan*/  clk_lsi; struct watchdog_device wdd; int /*<<< orphan*/  regs; int /*<<< orphan*/  has_pclk; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_device_id {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int RLR_MAX ; 
 int RLR_MIN ; 
 int /*<<< orphan*/  WATCHDOG_NOWAYOUT ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct stm32_iwdg* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32_iwdg*) ; 
 int stm32_iwdg_clk_init (struct platform_device*,struct stm32_iwdg*) ; 
 int /*<<< orphan*/  stm32_iwdg_info ; 
 int /*<<< orphan*/  stm32_iwdg_of_match ; 
 int /*<<< orphan*/  stm32_iwdg_ops ; 
 int watchdog_init_timeout (struct watchdog_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int watchdog_register_device (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct stm32_iwdg*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stm32_iwdg_probe(struct platform_device *pdev)
{
	struct watchdog_device *wdd;
	const struct of_device_id *match;
	struct stm32_iwdg *wdt;
	struct resource *res;
	int ret;

	match = of_match_device(stm32_iwdg_of_match, &pdev->dev);
	if (!match)
		return -ENODEV;

	wdt = devm_kzalloc(&pdev->dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	wdt->has_pclk = match->data;

	/* This is the timer base. */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	wdt->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(wdt->regs)) {
		dev_err(&pdev->dev, "Could not get resource\n");
		return PTR_ERR(wdt->regs);
	}

	ret = stm32_iwdg_clk_init(pdev, wdt);
	if (ret)
		return ret;

	/* Initialize struct watchdog_device. */
	wdd = &wdt->wdd;
	wdd->info = &stm32_iwdg_info;
	wdd->ops = &stm32_iwdg_ops;
	wdd->min_timeout = ((RLR_MIN + 1) * 256) / wdt->rate;
	wdd->max_hw_heartbeat_ms = ((RLR_MAX + 1) * 256 * 1000) / wdt->rate;
	wdd->parent = &pdev->dev;

	watchdog_set_drvdata(wdd, wdt);
	watchdog_set_nowayout(wdd, WATCHDOG_NOWAYOUT);

	ret = watchdog_init_timeout(wdd, 0, &pdev->dev);
	if (ret)
		dev_warn(&pdev->dev,
			 "unable to set timeout value, using default\n");

	ret = watchdog_register_device(wdd);
	if (ret) {
		dev_err(&pdev->dev, "failed to register watchdog device\n");
		goto err;
	}

	platform_set_drvdata(pdev, wdt);

	return 0;
err:
	clk_disable_unprepare(wdt->clk_lsi);
	clk_disable_unprepare(wdt->clk_pclk);

	return ret;
}