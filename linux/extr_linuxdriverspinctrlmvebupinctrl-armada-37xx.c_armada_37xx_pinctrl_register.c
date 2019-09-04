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
struct pinctrl_pin_desc {int number; int /*<<< orphan*/  name; } ;
struct pinctrl_desc {char* name; int npins; struct pinctrl_pin_desc* pins; int /*<<< orphan*/ * confops; int /*<<< orphan*/ * pmxops; int /*<<< orphan*/ * pctlops; int /*<<< orphan*/  owner; } ;
struct armada_37xx_pmx_func {int dummy; } ;
struct armada_37xx_pinctrl {int /*<<< orphan*/  pctl_dev; void* funcs; int /*<<< orphan*/  ngroups; int /*<<< orphan*/  groups; struct pinctrl_desc pctl; struct armada_37xx_pin_data* data; } ;
struct armada_37xx_pin_data {int nr_pins; int /*<<< orphan*/  name; int /*<<< orphan*/  ngroups; int /*<<< orphan*/  groups; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int armada_37xx_fill_func (struct armada_37xx_pinctrl*) ; 
 int armada_37xx_fill_group (struct armada_37xx_pinctrl*) ; 
 int /*<<< orphan*/  armada_37xx_pctrl_ops ; 
 int /*<<< orphan*/  armada_37xx_pinconf_ops ; 
 int /*<<< orphan*/  armada_37xx_pmx_ops ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* devm_kcalloc (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (int /*<<< orphan*/ *,struct pinctrl_desc*,struct armada_37xx_pinctrl*) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int armada_37xx_pinctrl_register(struct platform_device *pdev,
					struct armada_37xx_pinctrl *info)
{
	const struct armada_37xx_pin_data *pin_data = info->data;
	struct pinctrl_desc *ctrldesc = &info->pctl;
	struct pinctrl_pin_desc *pindesc, *pdesc;
	int pin, ret;

	info->groups = pin_data->groups;
	info->ngroups = pin_data->ngroups;

	ctrldesc->name = "armada_37xx-pinctrl";
	ctrldesc->owner = THIS_MODULE;
	ctrldesc->pctlops = &armada_37xx_pctrl_ops;
	ctrldesc->pmxops = &armada_37xx_pmx_ops;
	ctrldesc->confops = &armada_37xx_pinconf_ops;

	pindesc = devm_kcalloc(&pdev->dev,
			       pin_data->nr_pins, sizeof(*pindesc),
			       GFP_KERNEL);
	if (!pindesc)
		return -ENOMEM;

	ctrldesc->pins = pindesc;
	ctrldesc->npins = pin_data->nr_pins;

	pdesc = pindesc;
	for (pin = 0; pin < pin_data->nr_pins; pin++) {
		pdesc->number = pin;
		pdesc->name = kasprintf(GFP_KERNEL, "%s-%d",
					pin_data->name, pin);
		pdesc++;
	}

	/*
	 * we allocate functions for number of pins and hope there are
	 * fewer unique functions than pins available
	 */
	info->funcs = devm_kcalloc(&pdev->dev,
				   pin_data->nr_pins,
				   sizeof(struct armada_37xx_pmx_func),
				   GFP_KERNEL);
	if (!info->funcs)
		return -ENOMEM;


	ret = armada_37xx_fill_group(info);
	if (ret)
		return ret;

	ret = armada_37xx_fill_func(info);
	if (ret)
		return ret;

	info->pctl_dev = devm_pinctrl_register(&pdev->dev, ctrldesc, info);
	if (IS_ERR(info->pctl_dev)) {
		dev_err(&pdev->dev, "could not register pinctrl driver\n");
		return PTR_ERR(info->pctl_dev);
	}

	return 0;
}