#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rpm_regulator_data {scalar_t__ name; int /*<<< orphan*/  supply; int /*<<< orphan*/  resource; int /*<<< orphan*/  template; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {struct qcom_rpm_reg* driver_data; TYPE_1__* dev; } ;
struct TYPE_7__ {int id; int /*<<< orphan*/  of_parse_cb; scalar_t__ of_match; int /*<<< orphan*/  supply_name; scalar_t__ name; int /*<<< orphan*/  type; int /*<<< orphan*/  owner; } ;
struct qcom_rpm_reg {TYPE_3__ desc; struct qcom_rpm* rpm; int /*<<< orphan*/  resource; TYPE_1__* dev; int /*<<< orphan*/  lock; } ;
struct qcom_rpm {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
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
 struct qcom_rpm* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct qcom_rpm_reg* devm_kmalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,TYPE_3__*,struct regulator_config*) ; 
 int /*<<< orphan*/  memcpy (struct qcom_rpm_reg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  rpm_of_match ; 
 int /*<<< orphan*/  rpm_reg_of_parse ; 

__attribute__((used)) static int rpm_reg_probe(struct platform_device *pdev)
{
	const struct rpm_regulator_data *reg;
	const struct of_device_id *match;
	struct regulator_config config = { };
	struct regulator_dev *rdev;
	struct qcom_rpm_reg *vreg;
	struct qcom_rpm *rpm;

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
		vreg = devm_kmalloc(&pdev->dev, sizeof(*vreg), GFP_KERNEL);
		if (!vreg)
			return -ENOMEM;

		memcpy(vreg, reg->template, sizeof(*vreg));
		mutex_init(&vreg->lock);

		vreg->dev = &pdev->dev;
		vreg->resource = reg->resource;
		vreg->rpm = rpm;

		vreg->desc.id = -1;
		vreg->desc.owner = THIS_MODULE;
		vreg->desc.type = REGULATOR_VOLTAGE;
		vreg->desc.name = reg->name;
		vreg->desc.supply_name = reg->supply;
		vreg->desc.of_match = reg->name;
		vreg->desc.of_parse_cb = rpm_reg_of_parse;

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