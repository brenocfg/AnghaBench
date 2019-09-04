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
struct watchdog_device {int /*<<< orphan*/  bootstatus; int /*<<< orphan*/  timeout; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct pic32_wdt {int /*<<< orphan*/  clk; int /*<<< orphan*/  rst_base; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIC32_BASE_RESET ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WATCHDOG_NOWAYOUT ; 
 int /*<<< orphan*/  WDIOF_CARDRESET ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct pic32_wdt* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct watchdog_device pic32_wdd ; 
 scalar_t__ pic32_wdt_bootstatus (struct pic32_wdt*) ; 
 int /*<<< orphan*/  pic32_wdt_get_timeout_secs (struct pic32_wdt*,int /*<<< orphan*/ *) ; 
 scalar_t__ pic32_wdt_is_win_enabled (struct pic32_wdt*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct watchdog_device*) ; 
 int watchdog_register_device (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct pic32_wdt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pic32_wdt_drv_probe(struct platform_device *pdev)
{
	int ret;
	struct watchdog_device *wdd = &pic32_wdd;
	struct pic32_wdt *wdt;
	struct resource *mem;

	wdt = devm_kzalloc(&pdev->dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	wdt->regs = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(wdt->regs))
		return PTR_ERR(wdt->regs);

	wdt->rst_base = devm_ioremap(&pdev->dev, PIC32_BASE_RESET, 0x10);
	if (!wdt->rst_base)
		return -ENOMEM;

	wdt->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(wdt->clk)) {
		dev_err(&pdev->dev, "clk not found\n");
		return PTR_ERR(wdt->clk);
	}

	ret = clk_prepare_enable(wdt->clk);
	if (ret) {
		dev_err(&pdev->dev, "clk enable failed\n");
		return ret;
	}

	if (pic32_wdt_is_win_enabled(wdt)) {
		dev_err(&pdev->dev, "windowed-clear mode is not supported.\n");
		ret = -ENODEV;
		goto out_disable_clk;
	}

	wdd->timeout = pic32_wdt_get_timeout_secs(wdt, &pdev->dev);
	if (!wdd->timeout) {
		dev_err(&pdev->dev,
			"failed to read watchdog register timeout\n");
		ret = -EINVAL;
		goto out_disable_clk;
	}

	dev_info(&pdev->dev, "timeout %d\n", wdd->timeout);

	wdd->bootstatus = pic32_wdt_bootstatus(wdt) ? WDIOF_CARDRESET : 0;

	watchdog_set_nowayout(wdd, WATCHDOG_NOWAYOUT);
	watchdog_set_drvdata(wdd, wdt);

	ret = watchdog_register_device(wdd);
	if (ret) {
		dev_err(&pdev->dev, "watchdog register failed, err %d\n", ret);
		goto out_disable_clk;
	}

	platform_set_drvdata(pdev, wdd);

	return 0;

out_disable_clk:
	clk_disable_unprepare(wdt->clk);

	return ret;
}