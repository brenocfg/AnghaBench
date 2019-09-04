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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int base; int npwm; int of_pwm_n_cells; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; } ;
struct kona_pwmc {TYPE_1__ chip; scalar_t__ clk; scalar_t__ base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 scalar_t__ PWM_CONTROL_OFFSET ; 
 int PWM_CONTROL_TYPE_SHIFT (unsigned int) ; 
 int /*<<< orphan*/  PWM_POLARITY_INVERSED ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct kona_pwmc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kona_pwm_ops ; 
 int /*<<< orphan*/  of_pwm_xlate_with_flags ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct kona_pwmc*) ; 
 int pwmchip_add_with_polarity (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int kona_pwmc_probe(struct platform_device *pdev)
{
	struct kona_pwmc *kp;
	struct resource *res;
	unsigned int chan;
	unsigned int value = 0;
	int ret = 0;

	kp = devm_kzalloc(&pdev->dev, sizeof(*kp), GFP_KERNEL);
	if (kp == NULL)
		return -ENOMEM;

	platform_set_drvdata(pdev, kp);

	kp->chip.dev = &pdev->dev;
	kp->chip.ops = &kona_pwm_ops;
	kp->chip.base = -1;
	kp->chip.npwm = 6;
	kp->chip.of_xlate = of_pwm_xlate_with_flags;
	kp->chip.of_pwm_n_cells = 3;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	kp->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(kp->base))
		return PTR_ERR(kp->base);

	kp->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(kp->clk)) {
		dev_err(&pdev->dev, "failed to get clock: %ld\n",
			PTR_ERR(kp->clk));
		return PTR_ERR(kp->clk);
	}

	ret = clk_prepare_enable(kp->clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to enable clock: %d\n", ret);
		return ret;
	}

	/* Set push/pull for all channels */
	for (chan = 0; chan < kp->chip.npwm; chan++)
		value |= (1 << PWM_CONTROL_TYPE_SHIFT(chan));

	writel(value, kp->base + PWM_CONTROL_OFFSET);

	clk_disable_unprepare(kp->clk);

	ret = pwmchip_add_with_polarity(&kp->chip, PWM_POLARITY_INVERSED);
	if (ret < 0)
		dev_err(&pdev->dev, "failed to add PWM chip: %d\n", ret);

	return ret;
}