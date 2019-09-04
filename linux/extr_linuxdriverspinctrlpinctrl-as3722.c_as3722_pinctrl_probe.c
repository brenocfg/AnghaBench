#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_8__* parent; int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; TYPE_4__* parent; } ;
struct as3722_pctrl_info {TYPE_1__ gpio_chip; int /*<<< orphan*/  pctl; void* num_pin_groups; void* pin_groups; void* num_functions; void* functions; void* num_pins; void* pins; int /*<<< orphan*/  as3722; TYPE_4__* dev; } ;
struct TYPE_15__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_14__ {void* npins; void* pins; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  AS3722_PIN_NUM ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 TYPE_1__ as3722_gpio_chip ; 
 void* as3722_pin_function ; 
 TYPE_5__ as3722_pinctrl_desc ; 
 void* as3722_pingroups ; 
 void* as3722_pins_desc ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  dev_get_drvdata (TYPE_8__*) ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 struct as3722_pctrl_info* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pinctrl_register (TYPE_4__*,TYPE_5__*,struct as3722_pctrl_info*) ; 
 int gpiochip_add_data (TYPE_1__*,struct as3722_pctrl_info*) ; 
 int gpiochip_add_pin_range (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiochip_remove (TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct as3722_pctrl_info*) ; 

__attribute__((used)) static int as3722_pinctrl_probe(struct platform_device *pdev)
{
	struct as3722_pctrl_info *as_pci;
	int ret;

	as_pci = devm_kzalloc(&pdev->dev, sizeof(*as_pci), GFP_KERNEL);
	if (!as_pci)
		return -ENOMEM;

	as_pci->dev = &pdev->dev;
	as_pci->dev->of_node = pdev->dev.parent->of_node;
	as_pci->as3722 = dev_get_drvdata(pdev->dev.parent);
	platform_set_drvdata(pdev, as_pci);

	as_pci->pins = as3722_pins_desc;
	as_pci->num_pins = ARRAY_SIZE(as3722_pins_desc);
	as_pci->functions = as3722_pin_function;
	as_pci->num_functions = ARRAY_SIZE(as3722_pin_function);
	as_pci->pin_groups = as3722_pingroups;
	as_pci->num_pin_groups = ARRAY_SIZE(as3722_pingroups);
	as3722_pinctrl_desc.name = dev_name(&pdev->dev);
	as3722_pinctrl_desc.pins = as3722_pins_desc;
	as3722_pinctrl_desc.npins = ARRAY_SIZE(as3722_pins_desc);
	as_pci->pctl = devm_pinctrl_register(&pdev->dev, &as3722_pinctrl_desc,
					     as_pci);
	if (IS_ERR(as_pci->pctl)) {
		dev_err(&pdev->dev, "Couldn't register pinctrl driver\n");
		return PTR_ERR(as_pci->pctl);
	}

	as_pci->gpio_chip = as3722_gpio_chip;
	as_pci->gpio_chip.parent = &pdev->dev;
	as_pci->gpio_chip.of_node = pdev->dev.parent->of_node;
	ret = gpiochip_add_data(&as_pci->gpio_chip, as_pci);
	if (ret < 0) {
		dev_err(&pdev->dev, "Couldn't register gpiochip, %d\n", ret);
		return ret;
	}

	ret = gpiochip_add_pin_range(&as_pci->gpio_chip, dev_name(&pdev->dev),
				0, 0, AS3722_PIN_NUM);
	if (ret < 0) {
		dev_err(&pdev->dev, "Couldn't add pin range, %d\n", ret);
		goto fail_range_add;
	}

	return 0;

fail_range_add:
	gpiochip_remove(&as_pci->gpio_chip);
	return ret;
}