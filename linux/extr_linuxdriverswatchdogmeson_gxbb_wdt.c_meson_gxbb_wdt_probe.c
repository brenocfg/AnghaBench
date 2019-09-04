#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int min_timeout; int /*<<< orphan*/  timeout; int /*<<< orphan*/  max_hw_heartbeat_ms; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * info; int /*<<< orphan*/ * parent; } ;
struct meson_gxbb_wdt {scalar_t__ clk; TYPE_1__ wdt_dev; scalar_t__ reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_TIMEOUT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GXBB_WDT_CTRL_CLKDIV_EN ; 
 int GXBB_WDT_CTRL_CLK_EN ; 
 int GXBB_WDT_CTRL_DIV_MASK ; 
 int GXBB_WDT_CTRL_EE_RESET ; 
 scalar_t__ GXBB_WDT_CTRL_REG ; 
 int /*<<< orphan*/  GXBB_WDT_TCNT_SETUP_MASK ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_get_rate (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct meson_gxbb_wdt* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_gxbb_wdt_info ; 
 int /*<<< orphan*/  meson_gxbb_wdt_ops ; 
 int /*<<< orphan*/  meson_gxbb_wdt_set_timeout (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct meson_gxbb_wdt*) ; 
 int watchdog_register_device (TYPE_1__*) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (TYPE_1__*,struct meson_gxbb_wdt*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int meson_gxbb_wdt_probe(struct platform_device *pdev)
{
	struct meson_gxbb_wdt *data;
	struct resource *res;
	int ret;

	data = devm_kzalloc(&pdev->dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	data->reg_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(data->reg_base))
		return PTR_ERR(data->reg_base);

	data->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(data->clk))
		return PTR_ERR(data->clk);

	ret = clk_prepare_enable(data->clk);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, data);

	data->wdt_dev.parent = &pdev->dev;
	data->wdt_dev.info = &meson_gxbb_wdt_info;
	data->wdt_dev.ops = &meson_gxbb_wdt_ops;
	data->wdt_dev.max_hw_heartbeat_ms = GXBB_WDT_TCNT_SETUP_MASK;
	data->wdt_dev.min_timeout = 1;
	data->wdt_dev.timeout = DEFAULT_TIMEOUT;
	watchdog_set_drvdata(&data->wdt_dev, data);

	/* Setup with 1ms timebase */
	writel(((clk_get_rate(data->clk) / 1000) & GXBB_WDT_CTRL_DIV_MASK) |
		GXBB_WDT_CTRL_EE_RESET |
		GXBB_WDT_CTRL_CLK_EN |
		GXBB_WDT_CTRL_CLKDIV_EN,
		data->reg_base + GXBB_WDT_CTRL_REG);

	meson_gxbb_wdt_set_timeout(&data->wdt_dev, data->wdt_dev.timeout);

	ret = watchdog_register_device(&data->wdt_dev);
	if (ret) {
		clk_disable_unprepare(data->clk);
		return ret;
	}

	return 0;
}