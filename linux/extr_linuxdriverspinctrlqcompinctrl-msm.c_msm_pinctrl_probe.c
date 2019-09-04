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
struct msm_pinctrl_soc_data {int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; } ;
struct TYPE_2__ {int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; int /*<<< orphan*/  name; int /*<<< orphan*/ * confops; int /*<<< orphan*/ * pmxops; int /*<<< orphan*/ * pctlops; int /*<<< orphan*/  owner; } ;
struct msm_pinctrl {scalar_t__ irq; int /*<<< orphan*/  pctrl; TYPE_1__ desc; struct msm_pinctrl_soc_data const* soc; int /*<<< orphan*/  regs; int /*<<< orphan*/  lock; int /*<<< orphan*/  chip; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct msm_pinctrl* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (int /*<<< orphan*/ *,TYPE_1__*,struct msm_pinctrl*) ; 
 int msm_gpio_init (struct msm_pinctrl*) ; 
 int /*<<< orphan*/  msm_gpio_template ; 
 int /*<<< orphan*/  msm_pinconf_ops ; 
 int /*<<< orphan*/  msm_pinctrl_ops ; 
 int /*<<< orphan*/  msm_pinctrl_setup_pm_reset (struct msm_pinctrl*) ; 
 int /*<<< orphan*/  msm_pinmux_ops ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct msm_pinctrl*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

int msm_pinctrl_probe(struct platform_device *pdev,
		      const struct msm_pinctrl_soc_data *soc_data)
{
	struct msm_pinctrl *pctrl;
	struct resource *res;
	int ret;

	pctrl = devm_kzalloc(&pdev->dev, sizeof(*pctrl), GFP_KERNEL);
	if (!pctrl)
		return -ENOMEM;

	pctrl->dev = &pdev->dev;
	pctrl->soc = soc_data;
	pctrl->chip = msm_gpio_template;

	raw_spin_lock_init(&pctrl->lock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pctrl->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pctrl->regs))
		return PTR_ERR(pctrl->regs);

	msm_pinctrl_setup_pm_reset(pctrl);

	pctrl->irq = platform_get_irq(pdev, 0);
	if (pctrl->irq < 0) {
		dev_err(&pdev->dev, "No interrupt defined for msmgpio\n");
		return pctrl->irq;
	}

	pctrl->desc.owner = THIS_MODULE;
	pctrl->desc.pctlops = &msm_pinctrl_ops;
	pctrl->desc.pmxops = &msm_pinmux_ops;
	pctrl->desc.confops = &msm_pinconf_ops;
	pctrl->desc.name = dev_name(&pdev->dev);
	pctrl->desc.pins = pctrl->soc->pins;
	pctrl->desc.npins = pctrl->soc->npins;

	pctrl->pctrl = devm_pinctrl_register(&pdev->dev, &pctrl->desc, pctrl);
	if (IS_ERR(pctrl->pctrl)) {
		dev_err(&pdev->dev, "Couldn't register pinctrl driver\n");
		return PTR_ERR(pctrl->pctrl);
	}

	ret = msm_gpio_init(pctrl);
	if (ret)
		return ret;

	platform_set_drvdata(pdev, pctrl);

	dev_dbg(&pdev->dev, "Probed Qualcomm pinctrl driver\n");

	return 0;
}