#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct owl_pinctrl_soc_data {int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; } ;
struct TYPE_4__ {int /*<<< orphan*/  free; int /*<<< orphan*/  request; int /*<<< orphan*/  set; int /*<<< orphan*/  get; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  direction_input; } ;
struct owl_pinctrl {int num_irq; int* irq; int /*<<< orphan*/  clk; int /*<<< orphan*/  pctrldev; int /*<<< orphan*/ * dev; struct owl_pinctrl_soc_data* soc; TYPE_1__ chip; int /*<<< orphan*/  lock; int /*<<< orphan*/  base; } ;
struct TYPE_5__ {int /*<<< orphan*/  npins; int /*<<< orphan*/  pins; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 struct owl_pinctrl* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (int /*<<< orphan*/ *,TYPE_2__*,struct owl_pinctrl*) ; 
 int /*<<< orphan*/  owl_gpio_direction_input ; 
 int /*<<< orphan*/  owl_gpio_direction_output ; 
 int /*<<< orphan*/  owl_gpio_free ; 
 int /*<<< orphan*/  owl_gpio_get ; 
 int owl_gpio_init (struct owl_pinctrl*) ; 
 int /*<<< orphan*/  owl_gpio_request ; 
 int /*<<< orphan*/  owl_gpio_set ; 
 TYPE_2__ owl_pinctrl_desc ; 
 int platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_irq_count (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct owl_pinctrl*) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 

int owl_pinctrl_probe(struct platform_device *pdev,
				struct owl_pinctrl_soc_data *soc_data)
{
	struct resource *res;
	struct owl_pinctrl *pctrl;
	int ret, i;

	pctrl = devm_kzalloc(&pdev->dev, sizeof(*pctrl), GFP_KERNEL);
	if (!pctrl)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pctrl->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pctrl->base))
		return PTR_ERR(pctrl->base);

	/* enable GPIO/MFP clock */
	pctrl->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(pctrl->clk)) {
		dev_err(&pdev->dev, "no clock defined\n");
		return PTR_ERR(pctrl->clk);
	}

	ret = clk_prepare_enable(pctrl->clk);
	if (ret) {
		dev_err(&pdev->dev, "clk enable failed\n");
		return ret;
	}

	raw_spin_lock_init(&pctrl->lock);

	owl_pinctrl_desc.name = dev_name(&pdev->dev);
	owl_pinctrl_desc.pins = soc_data->pins;
	owl_pinctrl_desc.npins = soc_data->npins;

	pctrl->chip.direction_input  = owl_gpio_direction_input;
	pctrl->chip.direction_output = owl_gpio_direction_output;
	pctrl->chip.get = owl_gpio_get;
	pctrl->chip.set = owl_gpio_set;
	pctrl->chip.request = owl_gpio_request;
	pctrl->chip.free = owl_gpio_free;

	pctrl->soc = soc_data;
	pctrl->dev = &pdev->dev;

	pctrl->pctrldev = devm_pinctrl_register(&pdev->dev,
					&owl_pinctrl_desc, pctrl);
	if (IS_ERR(pctrl->pctrldev)) {
		dev_err(&pdev->dev, "could not register Actions OWL pinmux driver\n");
		ret = PTR_ERR(pctrl->pctrldev);
		goto err_exit;
	}

	ret = platform_irq_count(pdev);
	if (ret < 0)
		goto err_exit;

	pctrl->num_irq = ret;

	pctrl->irq = devm_kcalloc(&pdev->dev, pctrl->num_irq,
					sizeof(*pctrl->irq), GFP_KERNEL);
	if (!pctrl->irq) {
		ret = -ENOMEM;
		goto err_exit;
	}

	for (i = 0; i < pctrl->num_irq ; i++) {
		ret = platform_get_irq(pdev, i);
		if (ret < 0)
			goto err_exit;
		pctrl->irq[i] = ret;
	}

	ret = owl_gpio_init(pctrl);
	if (ret)
		goto err_exit;

	platform_set_drvdata(pdev, pctrl);

	return 0;

err_exit:
	clk_disable_unprepare(pctrl->clk);

	return ret;
}