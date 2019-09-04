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
struct regulator_dev {int dummy; } ;
struct regulator_desc {int /*<<< orphan*/  id; } ;
struct regulator_config {int /*<<< orphan*/  regmap; void* driver_data; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct max77693_dev {int /*<<< orphan*/  dev; } ;
typedef  enum max77693_types { ____Placeholder_max77693_types } max77693_types ;
struct TYPE_4__ {int driver_data; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct regulator_desc*) ; 
 int ENODEV ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
#define  TYPE_MAX77693 129 
#define  TYPE_MAX77843 128 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 struct max77693_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_2__*,struct regulator_desc const*,struct regulator_config*) ; 
 int /*<<< orphan*/  max77693_chg_reg_data ; 
 int /*<<< orphan*/  max77693_get_regmap (int,struct max77693_dev*,int /*<<< orphan*/ ) ; 
 struct regulator_desc* max77693_supported_regulators ; 
 int /*<<< orphan*/  max77843_chg_reg_data ; 
 struct regulator_desc* max77843_supported_regulators ; 
 TYPE_1__* platform_get_device_id (struct platform_device*) ; 

__attribute__((used)) static int max77693_pmic_probe(struct platform_device *pdev)
{
	enum max77693_types type = platform_get_device_id(pdev)->driver_data;
	struct max77693_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	const struct regulator_desc *regulators;
	unsigned int regulators_size;
	int i;
	struct regulator_config config = { };

	config.dev = iodev->dev;

	switch (type) {
	case TYPE_MAX77693:
		regulators = max77693_supported_regulators;
		regulators_size = ARRAY_SIZE(max77693_supported_regulators);
		config.driver_data = (void *)&max77693_chg_reg_data;
		break;
	case TYPE_MAX77843:
		regulators = max77843_supported_regulators;
		regulators_size = ARRAY_SIZE(max77843_supported_regulators);
		config.driver_data = (void *)&max77843_chg_reg_data;
		break;
	default:
		dev_err(&pdev->dev, "Unsupported device type: %u\n", type);
		return -ENODEV;
	}

	for (i = 0; i < regulators_size; i++) {
		struct regulator_dev *rdev;

		config.regmap = max77693_get_regmap(type, iodev,
						    regulators[i].id);

		rdev = devm_regulator_register(&pdev->dev,
						&regulators[i], &config);
		if (IS_ERR(rdev)) {
			dev_err(&pdev->dev,
				"Failed to initialize regulator-%d\n", i);
			return PTR_ERR(rdev);
		}
	}

	return 0;
}