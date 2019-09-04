#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct regulator_dev {TYPE_2__ dev; TYPE_1__* desc; } ;
struct regulator_desc {char* name; char const* supply_name; } ;
struct regulator_config {struct axp20x_dev* driver_data; int /*<<< orphan*/  regmap; TYPE_5__* dev; } ;
struct TYPE_9__ {TYPE_5__* parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct axp20x_dev {int variant; int /*<<< orphan*/  regmap; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  AXP202_ID 135 
#define  AXP209_ID 134 
 int /*<<< orphan*/  AXP20X_OVER_TMP ; 
 int AXP20X_REG_ID_MAX ; 
#define  AXP221_ID 133 
#define  AXP223_ID 132 
 int AXP22X_DC1SW ; 
 int AXP22X_DC5LDO ; 
 size_t AXP22X_DCDC1 ; 
 size_t AXP22X_DCDC5 ; 
 int /*<<< orphan*/  AXP22X_MISC_N_VBUSEN_FUNC ; 
 int AXP22X_REG_ID_MAX ; 
 int AXP803_DC1SW ; 
#define  AXP803_ID 131 
 int AXP803_REG_ID_MAX ; 
#define  AXP806_ID 130 
 int AXP806_REG_ID_MAX ; 
 int AXP809_DC1SW ; 
 int AXP809_DC5LDO ; 
 int AXP809_DCDC1 ; 
 int AXP809_DCDC5 ; 
#define  AXP809_ID 129 
 int AXP809_REG_ID_MAX ; 
 int AXP813_FLDO3 ; 
#define  AXP813_ID 128 
 int AXP813_REG_ID_MAX ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 scalar_t__ axp20x_is_polyphase_slave (struct axp20x_dev*,int) ; 
 int /*<<< orphan*/  axp20x_regulator_parse_dt (struct platform_device*) ; 
 struct regulator_desc* axp20x_regulators ; 
 scalar_t__ axp20x_set_dcdc_workmode (struct regulator_dev*,int,int /*<<< orphan*/ ) ; 
 struct regulator_desc const axp22x_drivevbus_regulator ; 
 struct regulator_desc const* axp22x_regulators ; 
 struct regulator_desc const* axp803_regulators ; 
 struct regulator_desc* axp806_regulators ; 
 struct regulator_desc const* axp809_regulators ; 
 struct regulator_desc* axp813_regulators ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 struct axp20x_dev* dev_get_drvdata (TYPE_5__*) ; 
 struct regulator_desc* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_3__*,struct regulator_desc const*,struct regulator_config*) ; 
 int of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  of_property_read_string (int /*<<< orphan*/ ,char*,char const**) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int axp20x_regulator_probe(struct platform_device *pdev)
{
	struct regulator_dev *rdev;
	struct axp20x_dev *axp20x = dev_get_drvdata(pdev->dev.parent);
	const struct regulator_desc *regulators;
	struct regulator_config config = {
		.dev = pdev->dev.parent,
		.regmap = axp20x->regmap,
		.driver_data = axp20x,
	};
	int ret, i, nregulators;
	u32 workmode;
	const char *dcdc1_name = axp22x_regulators[AXP22X_DCDC1].name;
	const char *dcdc5_name = axp22x_regulators[AXP22X_DCDC5].name;
	bool drivevbus = false;

	switch (axp20x->variant) {
	case AXP202_ID:
	case AXP209_ID:
		regulators = axp20x_regulators;
		nregulators = AXP20X_REG_ID_MAX;
		break;
	case AXP221_ID:
	case AXP223_ID:
		regulators = axp22x_regulators;
		nregulators = AXP22X_REG_ID_MAX;
		drivevbus = of_property_read_bool(pdev->dev.parent->of_node,
						  "x-powers,drive-vbus-en");
		break;
	case AXP803_ID:
		regulators = axp803_regulators;
		nregulators = AXP803_REG_ID_MAX;
		drivevbus = of_property_read_bool(pdev->dev.parent->of_node,
						  "x-powers,drive-vbus-en");
		break;
	case AXP806_ID:
		regulators = axp806_regulators;
		nregulators = AXP806_REG_ID_MAX;
		break;
	case AXP809_ID:
		regulators = axp809_regulators;
		nregulators = AXP809_REG_ID_MAX;
		break;
	case AXP813_ID:
		regulators = axp813_regulators;
		nregulators = AXP813_REG_ID_MAX;
		drivevbus = of_property_read_bool(pdev->dev.parent->of_node,
						  "x-powers,drive-vbus-en");
		break;
	default:
		dev_err(&pdev->dev, "Unsupported AXP variant: %ld\n",
			axp20x->variant);
		return -EINVAL;
	}

	/* This only sets the dcdc freq. Ignore any errors */
	axp20x_regulator_parse_dt(pdev);

	for (i = 0; i < nregulators; i++) {
		const struct regulator_desc *desc = &regulators[i];
		struct regulator_desc *new_desc;

		/*
		 * If this regulator is a slave in a poly-phase setup,
		 * skip it, as its controls are bound to the master
		 * regulator and won't work.
		 */
		if (axp20x_is_polyphase_slave(axp20x, i))
			continue;

		/* Support for AXP813's FLDO3 is not implemented */
		if (axp20x->variant == AXP813_ID && i == AXP813_FLDO3)
			continue;

		/*
		 * Regulators DC1SW and DC5LDO are connected internally,
		 * so we have to handle their supply names separately.
		 *
		 * We always register the regulators in proper sequence,
		 * so the supply names are correctly read. See the last
		 * part of this loop to see where we save the DT defined
		 * name.
		 */
		if ((regulators == axp22x_regulators && i == AXP22X_DC1SW) ||
		    (regulators == axp803_regulators && i == AXP803_DC1SW) ||
		    (regulators == axp809_regulators && i == AXP809_DC1SW)) {
			new_desc = devm_kzalloc(&pdev->dev, sizeof(*desc),
						GFP_KERNEL);
			if (!new_desc)
				return -ENOMEM;

			*new_desc = regulators[i];
			new_desc->supply_name = dcdc1_name;
			desc = new_desc;
		}

		if ((regulators == axp22x_regulators && i == AXP22X_DC5LDO) ||
		    (regulators == axp809_regulators && i == AXP809_DC5LDO)) {
			new_desc = devm_kzalloc(&pdev->dev, sizeof(*desc),
						GFP_KERNEL);
			if (!new_desc)
				return -ENOMEM;

			*new_desc = regulators[i];
			new_desc->supply_name = dcdc5_name;
			desc = new_desc;
		}

		rdev = devm_regulator_register(&pdev->dev, desc, &config);
		if (IS_ERR(rdev)) {
			dev_err(&pdev->dev, "Failed to register %s\n",
				regulators[i].name);

			return PTR_ERR(rdev);
		}

		ret = of_property_read_u32(rdev->dev.of_node,
					   "x-powers,dcdc-workmode",
					   &workmode);
		if (!ret) {
			if (axp20x_set_dcdc_workmode(rdev, i, workmode))
				dev_err(&pdev->dev, "Failed to set workmode on %s\n",
					rdev->desc->name);
		}

		/*
		 * Save AXP22X DCDC1 / DCDC5 regulator names for later.
		 */
		if ((regulators == axp22x_regulators && i == AXP22X_DCDC1) ||
		    (regulators == axp809_regulators && i == AXP809_DCDC1))
			of_property_read_string(rdev->dev.of_node,
						"regulator-name",
						&dcdc1_name);

		if ((regulators == axp22x_regulators && i == AXP22X_DCDC5) ||
		    (regulators == axp809_regulators && i == AXP809_DCDC5))
			of_property_read_string(rdev->dev.of_node,
						"regulator-name",
						&dcdc5_name);
	}

	if (drivevbus) {
		/* Change N_VBUSEN sense pin to DRIVEVBUS output pin */
		regmap_update_bits(axp20x->regmap, AXP20X_OVER_TMP,
				   AXP22X_MISC_N_VBUSEN_FUNC, 0);
		rdev = devm_regulator_register(&pdev->dev,
					       &axp22x_drivevbus_regulator,
					       &config);
		if (IS_ERR(rdev)) {
			dev_err(&pdev->dev, "Failed to register drivevbus\n");
			return PTR_ERR(rdev);
		}
	}

	return 0;
}