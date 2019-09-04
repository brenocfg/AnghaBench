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
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_9__ {int priority; int /*<<< orphan*/  notifier_call; } ;
struct TYPE_8__ {int nr_resets; int /*<<< orphan*/  of_node; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; } ;
struct lpc18xx_rgu_data {int delay_us; void* clk_reg; void* clk_delay; TYPE_2__ restart_nb; TYPE_1__ rcdev; int /*<<< orphan*/  lock; void* base; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  clk_disable_unprepare (void*) ; 
 int clk_get_rate (void*) ; 
 int clk_prepare_enable (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_3__*,char*) ; 
 void* devm_clk_get (TYPE_3__*,char*) ; 
 void* devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 struct lpc18xx_rgu_data* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc18xx_rgu_ops ; 
 int /*<<< orphan*/  lpc18xx_rgu_restart ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lpc18xx_rgu_data*) ; 
 int register_restart_handler (TYPE_2__*) ; 
 int reset_controller_register (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lpc18xx_rgu_probe(struct platform_device *pdev)
{
	struct lpc18xx_rgu_data *rc;
	struct resource *res;
	u32 fcclk, firc;
	int ret;

	rc = devm_kzalloc(&pdev->dev, sizeof(*rc), GFP_KERNEL);
	if (!rc)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	rc->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(rc->base))
		return PTR_ERR(rc->base);

	rc->clk_reg = devm_clk_get(&pdev->dev, "reg");
	if (IS_ERR(rc->clk_reg)) {
		dev_err(&pdev->dev, "reg clock not found\n");
		return PTR_ERR(rc->clk_reg);
	}

	rc->clk_delay = devm_clk_get(&pdev->dev, "delay");
	if (IS_ERR(rc->clk_delay)) {
		dev_err(&pdev->dev, "delay clock not found\n");
		return PTR_ERR(rc->clk_delay);
	}

	ret = clk_prepare_enable(rc->clk_reg);
	if (ret) {
		dev_err(&pdev->dev, "unable to enable reg clock\n");
		return ret;
	}

	ret = clk_prepare_enable(rc->clk_delay);
	if (ret) {
		dev_err(&pdev->dev, "unable to enable delay clock\n");
		goto dis_clk_reg;
	}

	fcclk = clk_get_rate(rc->clk_reg) / USEC_PER_SEC;
	firc = clk_get_rate(rc->clk_delay) / USEC_PER_SEC;
	if (fcclk == 0 || firc == 0)
		rc->delay_us = 2;
	else
		rc->delay_us = DIV_ROUND_UP(fcclk, firc * firc);

	spin_lock_init(&rc->lock);

	rc->rcdev.owner = THIS_MODULE;
	rc->rcdev.nr_resets = 64;
	rc->rcdev.ops = &lpc18xx_rgu_ops;
	rc->rcdev.of_node = pdev->dev.of_node;

	platform_set_drvdata(pdev, rc);

	ret = reset_controller_register(&rc->rcdev);
	if (ret) {
		dev_err(&pdev->dev, "unable to register device\n");
		goto dis_clks;
	}

	rc->restart_nb.priority = 192,
	rc->restart_nb.notifier_call = lpc18xx_rgu_restart,
	ret = register_restart_handler(&rc->restart_nb);
	if (ret)
		dev_warn(&pdev->dev, "failed to register restart handler\n");

	return 0;

dis_clks:
	clk_disable_unprepare(rc->clk_delay);
dis_clk_reg:
	clk_disable_unprepare(rc->clk_reg);

	return ret;
}