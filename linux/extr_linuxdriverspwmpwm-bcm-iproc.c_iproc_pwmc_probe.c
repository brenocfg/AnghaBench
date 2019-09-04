#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int base; int npwm; int of_pwm_n_cells; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; } ;
struct iproc_pwmc {scalar_t__ clk; TYPE_1__ chip; scalar_t__ base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IPROC_PWM_CTRL_OFFSET ; 
 int IPROC_PWM_CTRL_POLARITY_SHIFT (unsigned int) ; 
 int IPROC_PWM_CTRL_TYPE_SHIFT (unsigned int) ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct iproc_pwmc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iproc_pwm_ops ; 
 int /*<<< orphan*/  of_pwm_xlate_with_flags ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iproc_pwmc*) ; 
 int pwmchip_add (TYPE_1__*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int iproc_pwmc_probe(struct platform_device *pdev)
{
	struct iproc_pwmc *ip;
	struct resource *res;
	unsigned int i;
	u32 value;
	int ret;

	ip = devm_kzalloc(&pdev->dev, sizeof(*ip), GFP_KERNEL);
	if (!ip)
		return -ENOMEM;

	platform_set_drvdata(pdev, ip);

	ip->chip.dev = &pdev->dev;
	ip->chip.ops = &iproc_pwm_ops;
	ip->chip.base = -1;
	ip->chip.npwm = 4;
	ip->chip.of_xlate = of_pwm_xlate_with_flags;
	ip->chip.of_pwm_n_cells = 3;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ip->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ip->base))
		return PTR_ERR(ip->base);

	ip->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(ip->clk)) {
		dev_err(&pdev->dev, "failed to get clock: %ld\n",
			PTR_ERR(ip->clk));
		return PTR_ERR(ip->clk);
	}

	ret = clk_prepare_enable(ip->clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to enable clock: %d\n", ret);
		return ret;
	}

	/* Set full drive and normal polarity for all channels */
	value = readl(ip->base + IPROC_PWM_CTRL_OFFSET);

	for (i = 0; i < ip->chip.npwm; i++) {
		value &= ~(1 << IPROC_PWM_CTRL_TYPE_SHIFT(i));
		value |= 1 << IPROC_PWM_CTRL_POLARITY_SHIFT(i);
	}

	writel(value, ip->base + IPROC_PWM_CTRL_OFFSET);

	ret = pwmchip_add(&ip->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to add PWM chip: %d\n", ret);
		clk_disable_unprepare(ip->clk);
	}

	return ret;
}