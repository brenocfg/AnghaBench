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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct lpass_variant {int dummy; } ;
struct lpass_data {scalar_t__ lpaif_irq; int /*<<< orphan*/  lpaif_map; struct lpass_variant* variant; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  LPAIF_IRQEN_REG (struct lpass_variant*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPAIF_IRQ_PORT_HOST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int devm_request_irq (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct lpass_data*) ; 
 int devm_snd_soc_register_component (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpass_component_driver ; 
 int /*<<< orphan*/  lpass_platform_lpaif_irq ; 
 struct lpass_data* platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ platform_get_irq_byname (struct platform_device*,char*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int asoc_qcom_lpass_platform_register(struct platform_device *pdev)
{
	struct lpass_data *drvdata = platform_get_drvdata(pdev);
	struct lpass_variant *v = drvdata->variant;
	int ret;

	drvdata->lpaif_irq = platform_get_irq_byname(pdev, "lpass-irq-lpaif");
	if (drvdata->lpaif_irq < 0)
		return -ENODEV;

	/* ensure audio hardware is disabled */
	ret = regmap_write(drvdata->lpaif_map,
			LPAIF_IRQEN_REG(v, LPAIF_IRQ_PORT_HOST), 0);
	if (ret) {
		dev_err(&pdev->dev, "error writing to irqen reg: %d\n", ret);
		return ret;
	}

	ret = devm_request_irq(&pdev->dev, drvdata->lpaif_irq,
			lpass_platform_lpaif_irq, IRQF_TRIGGER_RISING,
			"lpass-irq-lpaif", drvdata);
	if (ret) {
		dev_err(&pdev->dev, "irq request failed: %d\n", ret);
		return ret;
	}


	return devm_snd_soc_register_component(&pdev->dev,
			&lpass_component_driver, NULL, 0);
}