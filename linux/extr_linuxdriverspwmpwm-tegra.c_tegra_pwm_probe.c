#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int base; int /*<<< orphan*/  npwm; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; } ;
struct tegra_pwm_chip {int /*<<< orphan*/  rst; TYPE_1__ chip; TYPE_2__* soc; int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_rate; int /*<<< orphan*/  regs; int /*<<< orphan*/ * dev; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  max_frequency; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct tegra_pwm_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_reset_control_get_exclusive (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tegra_pwm_chip*) ; 
 int pwmchip_add (TYPE_1__*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_control_deassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_pwm_ops ; 

__attribute__((used)) static int tegra_pwm_probe(struct platform_device *pdev)
{
	struct tegra_pwm_chip *pwm;
	struct resource *r;
	int ret;

	pwm = devm_kzalloc(&pdev->dev, sizeof(*pwm), GFP_KERNEL);
	if (!pwm)
		return -ENOMEM;

	pwm->soc = of_device_get_match_data(&pdev->dev);
	pwm->dev = &pdev->dev;

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pwm->regs = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(pwm->regs))
		return PTR_ERR(pwm->regs);

	platform_set_drvdata(pdev, pwm);

	pwm->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(pwm->clk))
		return PTR_ERR(pwm->clk);

	/* Set maximum frequency of the IP */
	ret = clk_set_rate(pwm->clk, pwm->soc->max_frequency);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to set max frequency: %d\n", ret);
		return ret;
	}

	/*
	 * The requested and configured frequency may differ due to
	 * clock register resolutions. Get the configured frequency
	 * so that PWM period can be calculated more accurately.
	 */
	pwm->clk_rate = clk_get_rate(pwm->clk);

	pwm->rst = devm_reset_control_get_exclusive(&pdev->dev, "pwm");
	if (IS_ERR(pwm->rst)) {
		ret = PTR_ERR(pwm->rst);
		dev_err(&pdev->dev, "Reset control is not found: %d\n", ret);
		return ret;
	}

	reset_control_deassert(pwm->rst);

	pwm->chip.dev = &pdev->dev;
	pwm->chip.ops = &tegra_pwm_ops;
	pwm->chip.base = -1;
	pwm->chip.npwm = pwm->soc->num_channels;

	ret = pwmchip_add(&pwm->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "pwmchip_add() failed: %d\n", ret);
		reset_control_assert(pwm->rst);
		return ret;
	}

	return 0;
}