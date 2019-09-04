#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_9__ {struct TYPE_9__* parent; struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_8__ {int of_pwm_n_cells; int base; int /*<<< orphan*/  npwm; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/ * ops; TYPE_2__* dev; } ;
struct ehrpwm_pwm_chip {struct clk* tbclk; TYPE_1__ chip; struct clk* mmio_base; int /*<<< orphan*/  clk_rate; } ;
struct device_node {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  NUM_PWM_CHANNEL ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  clk_get_rate (struct clk*) ; 
 int clk_prepare (struct clk*) ; 
 int /*<<< orphan*/  clk_unprepare (struct clk*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 void* devm_clk_get (TYPE_2__*,char*) ; 
 struct clk* devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct ehrpwm_pwm_chip* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehrpwm_pwm_ops ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_pwm_xlate_with_flags ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ehrpwm_pwm_chip*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int pwmchip_add (TYPE_1__*) ; 

__attribute__((used)) static int ehrpwm_pwm_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct ehrpwm_pwm_chip *pc;
	struct resource *r;
	struct clk *clk;
	int ret;

	pc = devm_kzalloc(&pdev->dev, sizeof(*pc), GFP_KERNEL);
	if (!pc)
		return -ENOMEM;

	clk = devm_clk_get(&pdev->dev, "fck");
	if (IS_ERR(clk)) {
		if (of_device_is_compatible(np, "ti,am33xx-ecap")) {
			dev_warn(&pdev->dev, "Binding is obsolete.\n");
			clk = devm_clk_get(pdev->dev.parent, "fck");
		}
	}

	if (IS_ERR(clk)) {
		dev_err(&pdev->dev, "failed to get clock\n");
		return PTR_ERR(clk);
	}

	pc->clk_rate = clk_get_rate(clk);
	if (!pc->clk_rate) {
		dev_err(&pdev->dev, "failed to get clock rate\n");
		return -EINVAL;
	}

	pc->chip.dev = &pdev->dev;
	pc->chip.ops = &ehrpwm_pwm_ops;
	pc->chip.of_xlate = of_pwm_xlate_with_flags;
	pc->chip.of_pwm_n_cells = 3;
	pc->chip.base = -1;
	pc->chip.npwm = NUM_PWM_CHANNEL;

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pc->mmio_base = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(pc->mmio_base))
		return PTR_ERR(pc->mmio_base);

	/* Acquire tbclk for Time Base EHRPWM submodule */
	pc->tbclk = devm_clk_get(&pdev->dev, "tbclk");
	if (IS_ERR(pc->tbclk)) {
		dev_err(&pdev->dev, "Failed to get tbclk\n");
		return PTR_ERR(pc->tbclk);
	}

	ret = clk_prepare(pc->tbclk);
	if (ret < 0) {
		dev_err(&pdev->dev, "clk_prepare() failed: %d\n", ret);
		return ret;
	}

	ret = pwmchip_add(&pc->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "pwmchip_add() failed: %d\n", ret);
		goto err_clk_unprepare;
	}

	platform_set_drvdata(pdev, pc);
	pm_runtime_enable(&pdev->dev);

	return 0;

err_clk_unprepare:
	clk_unprepare(pc->tbclk);

	return ret;
}