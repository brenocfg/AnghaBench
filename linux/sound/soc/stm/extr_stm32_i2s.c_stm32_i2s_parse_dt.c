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
struct stm32_i2s_data {struct reset_control* x11kclk; struct reset_control* x8kclk; struct reset_control* i2sclk; struct reset_control* pclk; int /*<<< orphan*/  phys_addr; struct reset_control* base; struct regmap_config const* regmap_conf; } ;
struct resource {int /*<<< orphan*/  start; } ;
struct reset_control {int dummy; } ;
struct regmap_config {int dummy; } ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 struct reset_control* devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stm32_i2s_data*) ; 
 struct reset_control* devm_reset_control_get_exclusive (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_assert (struct reset_control*) ; 
 int /*<<< orphan*/  reset_control_deassert (struct reset_control*) ; 
 int /*<<< orphan*/  stm32_i2s_ids ; 
 int /*<<< orphan*/  stm32_i2s_isr ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int stm32_i2s_parse_dt(struct platform_device *pdev,
			      struct stm32_i2s_data *i2s)
{
	struct device_node *np = pdev->dev.of_node;
	const struct of_device_id *of_id;
	struct reset_control *rst;
	struct resource *res;
	int irq, ret;

	if (!np)
		return -ENODEV;

	of_id = of_match_device(stm32_i2s_ids, &pdev->dev);
	if (of_id)
		i2s->regmap_conf = (const struct regmap_config *)of_id->data;
	else
		return -EINVAL;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	i2s->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(i2s->base))
		return PTR_ERR(i2s->base);

	i2s->phys_addr = res->start;

	/* Get clocks */
	i2s->pclk = devm_clk_get(&pdev->dev, "pclk");
	if (IS_ERR(i2s->pclk)) {
		dev_err(&pdev->dev, "Could not get pclk\n");
		return PTR_ERR(i2s->pclk);
	}

	i2s->i2sclk = devm_clk_get(&pdev->dev, "i2sclk");
	if (IS_ERR(i2s->i2sclk)) {
		dev_err(&pdev->dev, "Could not get i2sclk\n");
		return PTR_ERR(i2s->i2sclk);
	}

	i2s->x8kclk = devm_clk_get(&pdev->dev, "x8k");
	if (IS_ERR(i2s->x8kclk)) {
		dev_err(&pdev->dev, "missing x8k parent clock\n");
		return PTR_ERR(i2s->x8kclk);
	}

	i2s->x11kclk = devm_clk_get(&pdev->dev, "x11k");
	if (IS_ERR(i2s->x11kclk)) {
		dev_err(&pdev->dev, "missing x11k parent clock\n");
		return PTR_ERR(i2s->x11kclk);
	}

	/* Get irqs */
	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	ret = devm_request_irq(&pdev->dev, irq, stm32_i2s_isr, IRQF_ONESHOT,
			       dev_name(&pdev->dev), i2s);
	if (ret) {
		dev_err(&pdev->dev, "irq request returned %d\n", ret);
		return ret;
	}

	/* Reset */
	rst = devm_reset_control_get_exclusive(&pdev->dev, NULL);
	if (!IS_ERR(rst)) {
		reset_control_assert(rst);
		udelay(2);
		reset_control_deassert(rst);
	}

	return 0;
}