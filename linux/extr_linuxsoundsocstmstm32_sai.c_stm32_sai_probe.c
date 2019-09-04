#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct stm32_sai_data {scalar_t__ irq; int /*<<< orphan*/ * set_sync; struct platform_device* pdev; struct reset_control* clk_x11k; struct reset_control* clk_x8k; struct reset_control* pclk; struct stm32_sai_conf* conf; struct reset_control* base; } ;
struct stm32_sai_conf {int dummy; } ;
struct resource {int dummy; } ;
struct reset_control {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct of_device_id {scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct reset_control*) ; 
 int PTR_ERR (struct reset_control*) ; 
 int /*<<< orphan*/  STM_SAI_IS_F4 (struct stm32_sai_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct reset_control* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct stm32_sai_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_of_platform_populate (int /*<<< orphan*/ *) ; 
 struct reset_control* devm_reset_control_get_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32_sai_data*) ; 
 int /*<<< orphan*/  reset_control_assert (struct reset_control*) ; 
 int /*<<< orphan*/  reset_control_deassert (struct reset_control*) ; 
 int /*<<< orphan*/  stm32_sai_ids ; 
 int /*<<< orphan*/  stm32_sai_set_sync ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int stm32_sai_probe(struct platform_device *pdev)
{
	struct stm32_sai_data *sai;
	struct reset_control *rst;
	struct resource *res;
	const struct of_device_id *of_id;

	sai = devm_kzalloc(&pdev->dev, sizeof(*sai), GFP_KERNEL);
	if (!sai)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	sai->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(sai->base))
		return PTR_ERR(sai->base);

	of_id = of_match_device(stm32_sai_ids, &pdev->dev);
	if (of_id)
		sai->conf = (struct stm32_sai_conf *)of_id->data;
	else
		return -EINVAL;

	if (!STM_SAI_IS_F4(sai)) {
		sai->pclk = devm_clk_get(&pdev->dev, "pclk");
		if (IS_ERR(sai->pclk)) {
			dev_err(&pdev->dev, "missing bus clock pclk\n");
			return PTR_ERR(sai->pclk);
		}
	}

	sai->clk_x8k = devm_clk_get(&pdev->dev, "x8k");
	if (IS_ERR(sai->clk_x8k)) {
		dev_err(&pdev->dev, "missing x8k parent clock\n");
		return PTR_ERR(sai->clk_x8k);
	}

	sai->clk_x11k = devm_clk_get(&pdev->dev, "x11k");
	if (IS_ERR(sai->clk_x11k)) {
		dev_err(&pdev->dev, "missing x11k parent clock\n");
		return PTR_ERR(sai->clk_x11k);
	}

	/* init irqs */
	sai->irq = platform_get_irq(pdev, 0);
	if (sai->irq < 0) {
		dev_err(&pdev->dev, "no irq for node %s\n", pdev->name);
		return sai->irq;
	}

	/* reset */
	rst = devm_reset_control_get_exclusive(&pdev->dev, NULL);
	if (!IS_ERR(rst)) {
		reset_control_assert(rst);
		udelay(2);
		reset_control_deassert(rst);
	}

	sai->pdev = pdev;
	sai->set_sync = &stm32_sai_set_sync;
	platform_set_drvdata(pdev, sai);

	return devm_of_platform_populate(&pdev->dev);
}