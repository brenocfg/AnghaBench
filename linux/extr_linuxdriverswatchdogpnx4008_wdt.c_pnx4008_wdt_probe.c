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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/ * parent; int /*<<< orphan*/  bootstatus; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDIOF_CARDRESET ; 
 int WDOG_RESET ; 
 int /*<<< orphan*/  WDTIM_RES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  heartbeat ; 
 int /*<<< orphan*/  nowayout ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ pnx4008_wdd ; 
 int /*<<< orphan*/  pnx4008_wdt_stop (TYPE_1__*) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_nowayout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_set_restart_priority (TYPE_1__*,int) ; 
 int /*<<< orphan*/  wdt_base ; 
 int /*<<< orphan*/  wdt_clk ; 

__attribute__((used)) static int pnx4008_wdt_probe(struct platform_device *pdev)
{
	struct resource *r;
	int ret = 0;

	watchdog_init_timeout(&pnx4008_wdd, heartbeat, &pdev->dev);

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	wdt_base = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(wdt_base))
		return PTR_ERR(wdt_base);

	wdt_clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(wdt_clk))
		return PTR_ERR(wdt_clk);

	ret = clk_prepare_enable(wdt_clk);
	if (ret)
		return ret;

	pnx4008_wdd.bootstatus = (readl(WDTIM_RES(wdt_base)) & WDOG_RESET) ?
			WDIOF_CARDRESET : 0;
	pnx4008_wdd.parent = &pdev->dev;
	watchdog_set_nowayout(&pnx4008_wdd, nowayout);
	watchdog_set_restart_priority(&pnx4008_wdd, 128);

	pnx4008_wdt_stop(&pnx4008_wdd);	/* disable for now */

	ret = watchdog_register_device(&pnx4008_wdd);
	if (ret < 0) {
		dev_err(&pdev->dev, "cannot register watchdog device\n");
		goto disable_clk;
	}

	dev_info(&pdev->dev, "heartbeat %d sec\n", pnx4008_wdd.timeout);

	return 0;

disable_clk:
	clk_disable_unprepare(wdt_clk);
	return ret;
}