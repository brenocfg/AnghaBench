#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int timeout; int max_timeout; int min_timeout; TYPE_5__* parent; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; } ;
struct rtd119x_watchdog_device {scalar_t__ clk; TYPE_1__ wdt_dev; scalar_t__ base; } ;
struct resource {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_5__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ RTD119X_TCWTR ; 
 int /*<<< orphan*/  RTD119X_TCWTR_WDCLR ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_get_rate (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  clk_put (scalar_t__) ; 
 scalar_t__ devm_ioremap_resource (TYPE_5__*,struct resource*) ; 
 struct rtd119x_watchdog_device* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int devm_watchdog_register_device (TYPE_5__*,TYPE_1__*) ; 
 scalar_t__ of_clk_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct rtd119x_watchdog_device*) ; 
 int /*<<< orphan*/  rtd119x_wdt_info ; 
 int /*<<< orphan*/  rtd119x_wdt_ops ; 
 int /*<<< orphan*/  rtd119x_wdt_set_timeout (TYPE_1__*,int) ; 
 int /*<<< orphan*/  rtd119x_wdt_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct rtd119x_watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_stop_on_reboot (TYPE_1__*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int rtd119x_wdt_probe(struct platform_device *pdev)
{
	struct rtd119x_watchdog_device *data;
	struct resource *res;
	int ret;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	data->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(data->base))
		return PTR_ERR(data->base);

	data->clk = of_clk_get(pdev->dev.of_node, 0);
	if (IS_ERR(data->clk))
		return PTR_ERR(data->clk);

	ret = clk_prepare_enable(data->clk);
	if (ret) {
		clk_put(data->clk);
		return ret;
	}

	data->wdt_dev.info = &rtd119x_wdt_info;
	data->wdt_dev.ops = &rtd119x_wdt_ops;
	data->wdt_dev.timeout = 120;
	data->wdt_dev.max_timeout = 0xffffffff / clk_get_rate(data->clk);
	data->wdt_dev.min_timeout = 1;
	data->wdt_dev.parent = &pdev->dev;

	watchdog_stop_on_reboot(&data->wdt_dev);
	watchdog_set_drvdata(&data->wdt_dev, data);
	platform_set_drvdata(pdev, data);

	writel_relaxed(RTD119X_TCWTR_WDCLR, data->base + RTD119X_TCWTR);
	rtd119x_wdt_set_timeout(&data->wdt_dev, data->wdt_dev.timeout);
	rtd119x_wdt_stop(&data->wdt_dev);

	ret = devm_watchdog_register_device(&pdev->dev, &data->wdt_dev);
	if (ret) {
		clk_disable_unprepare(data->clk);
		clk_put(data->clk);
		return ret;
	}

	return 0;
}