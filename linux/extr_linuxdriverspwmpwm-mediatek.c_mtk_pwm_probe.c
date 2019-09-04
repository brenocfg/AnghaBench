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
struct mtk_pwm_platform_data {int num_pwms; scalar_t__ has_clks; } ;
struct TYPE_2__ {int base; int npwm; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * dev; } ;
struct mtk_pwm_chip {TYPE_1__ chip; int /*<<< orphan*/ * clks; struct mtk_pwm_platform_data const* soc; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct mtk_pwm_chip* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mtk_pwm_clk_name ; 
 int /*<<< orphan*/  mtk_pwm_ops ; 
 struct mtk_pwm_platform_data* of_device_get_match_data (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mtk_pwm_chip*) ; 
 int pwmchip_add (TYPE_1__*) ; 

__attribute__((used)) static int mtk_pwm_probe(struct platform_device *pdev)
{
	const struct mtk_pwm_platform_data *data;
	struct mtk_pwm_chip *pc;
	struct resource *res;
	unsigned int i;
	int ret;

	pc = devm_kzalloc(&pdev->dev, sizeof(*pc), GFP_KERNEL);
	if (!pc)
		return -ENOMEM;

	data = of_device_get_match_data(&pdev->dev);
	if (data == NULL)
		return -EINVAL;
	pc->soc = data;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pc->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pc->regs))
		return PTR_ERR(pc->regs);

	for (i = 0; i < data->num_pwms + 2 && pc->soc->has_clks; i++) {
		pc->clks[i] = devm_clk_get(&pdev->dev, mtk_pwm_clk_name[i]);
		if (IS_ERR(pc->clks[i])) {
			dev_err(&pdev->dev, "clock: %s fail: %ld\n",
				mtk_pwm_clk_name[i], PTR_ERR(pc->clks[i]));
			return PTR_ERR(pc->clks[i]);
		}
	}

	platform_set_drvdata(pdev, pc);

	pc->chip.dev = &pdev->dev;
	pc->chip.ops = &mtk_pwm_ops;
	pc->chip.base = -1;
	pc->chip.npwm = data->num_pwms;

	ret = pwmchip_add(&pc->chip);
	if (ret < 0) {
		dev_err(&pdev->dev, "pwmchip_add() failed: %d\n", ret);
		return ret;
	}

	return 0;
}