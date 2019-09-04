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
struct pic32_dmt {int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WATCHDOG_NOWAYOUT ; 
 int /*<<< orphan*/  WDIOF_CARDRESET ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct pic32_dmt* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pic32_dmt_bootstatus (struct pic32_dmt*) ; 
 int /*<<< orphan*/  pic32_dmt_get_timeout_secs (struct pic32_dmt*) ; 
 struct watchdog_device pic32_dmt_wdd ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct watchdog_device*) ; 
 int watchdog_register_device (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (struct watchdog_device*,struct pic32_dmt*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (struct watchdog_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pic32_dmt_probe(struct platform_device *pdev)
{
	int ret;
	struct pic32_dmt *dmt;
	struct resource *mem;
	struct watchdog_device *wdd = &pic32_dmt_wdd;

	dmt = devm_kzalloc(&pdev->dev, sizeof(*dmt), GFP_KERNEL);
	if (!dmt)
		return -ENOMEM;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dmt->regs = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(dmt->regs))
		return PTR_ERR(dmt->regs);

	dmt->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(dmt->clk)) {
		dev_err(&pdev->dev, "clk not found\n");
		return PTR_ERR(dmt->clk);
	}

	ret = clk_prepare_enable(dmt->clk);
	if (ret)
		return ret;

	wdd->timeout = pic32_dmt_get_timeout_secs(dmt);
	if (!wdd->timeout) {
		dev_err(&pdev->dev,
			"failed to read watchdog register timeout\n");
		ret = -EINVAL;
		goto out_disable_clk;
	}

	dev_info(&pdev->dev, "timeout %d\n", wdd->timeout);

	wdd->bootstatus = pic32_dmt_bootstatus(dmt) ? WDIOF_CARDRESET : 0;

	watchdog_set_nowayout(wdd, WATCHDOG_NOWAYOUT);
	watchdog_set_drvdata(wdd, dmt);

	ret = watchdog_register_device(wdd);
	if (ret) {
		dev_err(&pdev->dev, "watchdog register failed, err %d\n", ret);
		goto out_disable_clk;
	}

	platform_set_drvdata(pdev, wdd);
	return 0;

out_disable_clk:
	clk_disable_unprepare(dmt->clk);
	return ret;
}