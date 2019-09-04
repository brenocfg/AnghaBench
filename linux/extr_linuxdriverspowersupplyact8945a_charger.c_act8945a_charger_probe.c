#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct power_supply_config {struct act8945a_charger* drv_data; int /*<<< orphan*/  of_node; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_8__ {char* name; int /*<<< orphan*/  type; int /*<<< orphan*/  num_properties; int /*<<< orphan*/  properties; int /*<<< orphan*/  get_property; } ;
struct act8945a_charger {int init_done; int /*<<< orphan*/  work; int /*<<< orphan*/  psy; TYPE_3__ desc; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int act8945a_charger_config (TYPE_1__*,struct act8945a_charger*) ; 
 int /*<<< orphan*/  act8945a_charger_get_property ; 
 int /*<<< orphan*/  act8945a_charger_props ; 
 int act8945a_enable_interrupt (struct act8945a_charger*) ; 
 int act8945a_set_supply_type (struct act8945a_charger*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  act8945a_status_changed ; 
 int /*<<< orphan*/  act8945a_work ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct act8945a_charger* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_power_supply_register (TYPE_1__*,TYPE_3__*,struct power_supply_config*) ; 
 int devm_request_irq (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct act8945a_charger*) ; 
 int of_irq_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct act8945a_charger*) ; 

__attribute__((used)) static int act8945a_charger_probe(struct platform_device *pdev)
{
	struct act8945a_charger *charger;
	struct power_supply_config psy_cfg = {};
	int irq, ret;

	charger = devm_kzalloc(&pdev->dev, sizeof(*charger), GFP_KERNEL);
	if (!charger)
		return -ENOMEM;

	charger->regmap = dev_get_regmap(pdev->dev.parent, NULL);
	if (!charger->regmap) {
		dev_err(&pdev->dev, "Parent did not provide regmap\n");
		return -EINVAL;
	}

	ret = act8945a_charger_config(&pdev->dev, charger);
	if (ret)
		return ret;

	irq = of_irq_get(pdev->dev.of_node, 0);
	if (irq <= 0) {
		dev_err(&pdev->dev, "failed to find IRQ number\n");
		return irq ?: -ENXIO;
	}

	ret = devm_request_irq(&pdev->dev, irq, act8945a_status_changed,
			       IRQF_TRIGGER_FALLING, "act8945a_interrupt",
			       charger);
	if (ret) {
		dev_err(&pdev->dev, "failed to request nIRQ pin IRQ\n");
		return ret;
	}

	charger->desc.name = "act8945a-charger";
	charger->desc.get_property = act8945a_charger_get_property;
	charger->desc.properties = act8945a_charger_props;
	charger->desc.num_properties = ARRAY_SIZE(act8945a_charger_props);

	ret = act8945a_set_supply_type(charger, &charger->desc.type);
	if (ret)
		return -EINVAL;

	psy_cfg.of_node	= pdev->dev.of_node;
	psy_cfg.drv_data = charger;

	charger->psy = devm_power_supply_register(&pdev->dev,
						  &charger->desc,
						  &psy_cfg);
	if (IS_ERR(charger->psy)) {
		dev_err(&pdev->dev, "failed to register power supply\n");
		return PTR_ERR(charger->psy);
	}

	platform_set_drvdata(pdev, charger);

	INIT_WORK(&charger->work, act8945a_work);

	ret = act8945a_enable_interrupt(charger);
	if (ret)
		return -EIO;

	charger->init_done = true;

	return 0;
}