#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rpm_regulator_data {scalar_t__ name; int /*<<< orphan*/  supply; int /*<<< orphan*/  desc; int /*<<< orphan*/  id; int /*<<< orphan*/  type; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {struct qcom_rpm_reg* driver_data; TYPE_1__* dev; } ;
struct qcom_smd_rpm {int dummy; } ;
struct TYPE_8__ {int id; scalar_t__ of_match; int /*<<< orphan*/  supply_name; scalar_t__ name; int /*<<< orphan*/  type; int /*<<< orphan*/  owner; } ;
struct qcom_rpm_reg {TYPE_2__ desc; struct qcom_smd_rpm* rpm; int /*<<< orphan*/  id; int /*<<< orphan*/  type; TYPE_1__* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {struct rpm_regulator_data* data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct qcom_smd_rpm* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct qcom_rpm_reg* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,TYPE_2__*,struct regulator_config*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  rpm_of_match ; 

__attribute__((used)) static int rpm_reg_probe(struct platform_device *pdev)
{
	const struct rpm_regulator_data *reg;
	const struct of_device_id *match;
	struct regulator_config config = { };
	struct regulator_dev *rdev;
	struct qcom_rpm_reg *vreg;
	struct qcom_smd_rpm *rpm;

	rpm = dev_get_drvdata(pdev->dev.parent);
	if (!rpm) {
		dev_err(&pdev->dev, "unable to retrieve handle to rpm\n");
		return -ENODEV;
	}

	match = of_match_device(rpm_of_match, &pdev->dev);
	if (!match) {
		dev_err(&pdev->dev, "failed to match device\n");
		return -ENODEV;
	}

	for (reg = match->data; reg->name; reg++) {
		vreg = devm_kzalloc(&pdev->dev, sizeof(*vreg), GFP_KERNEL);
		if (!vreg)
			return -ENOMEM;

		vreg->dev = &pdev->dev;
		vreg->type = reg->type;
		vreg->id = reg->id;
		vreg->rpm = rpm;

		memcpy(&vreg->desc, reg->desc, sizeof(vreg->desc));

		vreg->desc.id = -1;
		vreg->desc.owner = THIS_MODULE;
		vreg->desc.type = REGULATOR_VOLTAGE;
		vreg->desc.name = reg->name;
		vreg->desc.supply_name = reg->supply;
		vreg->desc.of_match = reg->name;

		config.dev = &pdev->dev;
		config.driver_data = vreg;
		rdev = devm_regulator_register(&pdev->dev, &vreg->desc, &config);
		if (IS_ERR(rdev)) {
			dev_err(&pdev->dev, "failed to register %s\n", reg->name);
			return PTR_ERR(rdev);
		}
	}

	return 0;
}