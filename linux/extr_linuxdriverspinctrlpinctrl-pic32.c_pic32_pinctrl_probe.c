#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct pic32_pinctrl {int /*<<< orphan*/  pctldev; void* npins; void* pins; void* nbanks; void* gpio_banks; void* ngroups; void* groups; void* nfunctions; void* functions; int /*<<< orphan*/  clk; int /*<<< orphan*/  reg_base; int /*<<< orphan*/ * dev; } ;
struct TYPE_3__ {void* num_custom_params; void* custom_params; void* npins; void* pins; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct pic32_pinctrl*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct pic32_pinctrl* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (int /*<<< orphan*/ *,TYPE_1__*,struct pic32_pinctrl*) ; 
 void* pic32_functions ; 
 void* pic32_gpio_banks ; 
 void* pic32_groups ; 
 void* pic32_mpp_bindings ; 
 TYPE_1__ pic32_pinctrl_desc ; 
 void* pic32_pins ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pic32_pinctrl_probe(struct platform_device *pdev)
{
	struct pic32_pinctrl *pctl;
	struct resource *res;
	int ret;

	pctl = devm_kzalloc(&pdev->dev, sizeof(*pctl), GFP_KERNEL);
	if (!pctl)
		return -ENOMEM;
	pctl->dev = &pdev->dev;
	dev_set_drvdata(&pdev->dev, pctl);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pctl->reg_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pctl->reg_base))
		return PTR_ERR(pctl->reg_base);

	pctl->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(pctl->clk)) {
		ret = PTR_ERR(pctl->clk);
		dev_err(&pdev->dev, "clk get failed\n");
		return ret;
	}

	ret = clk_prepare_enable(pctl->clk);
	if (ret) {
		dev_err(&pdev->dev, "clk enable failed\n");
		return ret;
	}

	pctl->pins = pic32_pins;
	pctl->npins = ARRAY_SIZE(pic32_pins);
	pctl->functions = pic32_functions;
	pctl->nfunctions = ARRAY_SIZE(pic32_functions);
	pctl->groups = pic32_groups;
	pctl->ngroups = ARRAY_SIZE(pic32_groups);
	pctl->gpio_banks = pic32_gpio_banks;
	pctl->nbanks = ARRAY_SIZE(pic32_gpio_banks);

	pic32_pinctrl_desc.pins = pctl->pins;
	pic32_pinctrl_desc.npins = pctl->npins;
	pic32_pinctrl_desc.custom_params = pic32_mpp_bindings;
	pic32_pinctrl_desc.num_custom_params = ARRAY_SIZE(pic32_mpp_bindings);

	pctl->pctldev = devm_pinctrl_register(&pdev->dev, &pic32_pinctrl_desc,
					      pctl);
	if (IS_ERR(pctl->pctldev)) {
		dev_err(&pdev->dev, "Failed to register pinctrl device\n");
		return PTR_ERR(pctl->pctldev);
	}

	return 0;
}