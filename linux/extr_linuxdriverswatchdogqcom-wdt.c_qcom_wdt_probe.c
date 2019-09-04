#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct resource {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct TYPE_9__ {int min_timeout; int max_timeout; int /*<<< orphan*/  timeout; int /*<<< orphan*/  bootstatus; TYPE_3__* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct qcom_wdt {int rate; int /*<<< orphan*/  clk; TYPE_1__ wdd; scalar_t__ const* layout; int /*<<< orphan*/  base; } ;
struct TYPE_10__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WDIOF_CARDRESET ; 
 int /*<<< orphan*/  WDT_STS ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct qcom_wdt* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,unsigned int) ; 
 scalar_t__* of_device_get_match_data (TYPE_3__*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct qcom_wdt*) ; 
 int /*<<< orphan*/  qcom_wdt_info ; 
 int /*<<< orphan*/  qcom_wdt_ops ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_init_timeout (TYPE_1__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  wdt_addr (struct qcom_wdt*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qcom_wdt_probe(struct platform_device *pdev)
{
	struct qcom_wdt *wdt;
	struct resource *res;
	struct device_node *np = pdev->dev.of_node;
	const u32 *regs;
	u32 percpu_offset;
	int ret;

	regs = of_device_get_match_data(&pdev->dev);
	if (!regs) {
		dev_err(&pdev->dev, "Unsupported QCOM WDT module\n");
		return -ENODEV;
	}

	wdt = devm_kzalloc(&pdev->dev, sizeof(*wdt), GFP_KERNEL);
	if (!wdt)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENOMEM;

	/* We use CPU0's DGT for the watchdog */
	if (of_property_read_u32(np, "cpu-offset", &percpu_offset))
		percpu_offset = 0;

	res->start += percpu_offset;
	res->end += percpu_offset;

	wdt->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(wdt->base))
		return PTR_ERR(wdt->base);

	wdt->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(wdt->clk)) {
		dev_err(&pdev->dev, "failed to get input clock\n");
		return PTR_ERR(wdt->clk);
	}

	ret = clk_prepare_enable(wdt->clk);
	if (ret) {
		dev_err(&pdev->dev, "failed to setup clock\n");
		return ret;
	}

	/*
	 * We use the clock rate to calculate the max timeout, so ensure it's
	 * not zero to avoid a divide-by-zero exception.
	 *
	 * WATCHDOG_CORE assumes units of seconds, if the WDT is clocked such
	 * that it would bite before a second elapses it's usefulness is
	 * limited.  Bail if this is the case.
	 */
	wdt->rate = clk_get_rate(wdt->clk);
	if (wdt->rate == 0 ||
	    wdt->rate > 0x10000000U) {
		dev_err(&pdev->dev, "invalid clock rate\n");
		ret = -EINVAL;
		goto err_clk_unprepare;
	}

	wdt->wdd.info = &qcom_wdt_info;
	wdt->wdd.ops = &qcom_wdt_ops;
	wdt->wdd.min_timeout = 1;
	wdt->wdd.max_timeout = 0x10000000U / wdt->rate;
	wdt->wdd.parent = &pdev->dev;
	wdt->layout = regs;

	if (readl(wdt_addr(wdt, WDT_STS)) & 1)
		wdt->wdd.bootstatus = WDIOF_CARDRESET;

	/*
	 * If 'timeout-sec' unspecified in devicetree, assume a 30 second
	 * default, unless the max timeout is less than 30 seconds, then use
	 * the max instead.
	 */
	wdt->wdd.timeout = min(wdt->wdd.max_timeout, 30U);
	watchdog_init_timeout(&wdt->wdd, 0, &pdev->dev);

	ret = watchdog_register_device(&wdt->wdd);
	if (ret) {
		dev_err(&pdev->dev, "failed to register watchdog\n");
		goto err_clk_unprepare;
	}

	platform_set_drvdata(pdev, wdt);
	return 0;

err_clk_unprepare:
	clk_disable_unprepare(wdt->clk);
	return ret;
}