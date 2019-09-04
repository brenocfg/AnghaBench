#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int of_pwm_n_cells; int base; int /*<<< orphan*/  npwm; int /*<<< orphan*/  of_xlate; int /*<<< orphan*/ * ops; TYPE_2__* dev; } ;
struct vt8500_chip {int /*<<< orphan*/  clk; TYPE_1__ chip; int /*<<< orphan*/  base; } ;
struct resource {int dummy; } ;
struct TYPE_7__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VT8500_NR_PWMS ; 
 int clk_prepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_2__*,struct resource*) ; 
 struct vt8500_chip* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_pwm_xlate_with_flags ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct vt8500_chip*) ; 
 int pwmchip_add (TYPE_1__*) ; 
 int /*<<< orphan*/  vt8500_pwm_ops ; 

__attribute__((used)) static int vt8500_pwm_probe(struct platform_device *pdev)
{
	struct vt8500_chip *chip;
	struct resource *r;
	struct device_node *np = pdev->dev.of_node;
	int ret;

	if (!np) {
		dev_err(&pdev->dev, "invalid devicetree node\n");
		return -EINVAL;
	}

	chip = devm_kzalloc(&pdev->dev, sizeof(*chip), GFP_KERNEL);
	if (chip == NULL)
		return -ENOMEM;

	chip->chip.dev = &pdev->dev;
	chip->chip.ops = &vt8500_pwm_ops;
	chip->chip.of_xlate = of_pwm_xlate_with_flags;
	chip->chip.of_pwm_n_cells = 3;
	chip->chip.base = -1;
	chip->chip.npwm = VT8500_NR_PWMS;

	chip->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(chip->clk)) {
		dev_err(&pdev->dev, "clock source not specified\n");
		return PTR_ERR(chip->clk);
	}

	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	chip->base = devm_ioremap_resource(&pdev->dev, r);
	if (IS_ERR(chip->base))
		return PTR_ERR(chip->base);

	ret = clk_prepare(chip->clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to prepare clock\n");
		return ret;
	}

	ret = pwmchip_add(&chip->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to add PWM chip\n");
		clk_unprepare(chip->clk);
		return ret;
	}

	platform_set_drvdata(pdev, chip);
	return ret;
}