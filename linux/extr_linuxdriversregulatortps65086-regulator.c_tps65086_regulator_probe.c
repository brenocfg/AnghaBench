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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tps65086 {TYPE_3__* dev; int /*<<< orphan*/  regmap; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  regmap; struct tps65086* driver_data; TYPE_2__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; TYPE_2__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 struct tps65086* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_2__*,int /*<<< orphan*/ *,struct regulator_config*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tps65086*) ; 
 TYPE_1__* regulators ; 

__attribute__((used)) static int tps65086_regulator_probe(struct platform_device *pdev)
{
	struct tps65086 *tps = dev_get_drvdata(pdev->dev.parent);
	struct regulator_config config = { };
	struct regulator_dev *rdev;
	int i;

	platform_set_drvdata(pdev, tps);

	config.dev = &pdev->dev;
	config.dev->of_node = tps->dev->of_node;
	config.driver_data = tps;
	config.regmap = tps->regmap;

	for (i = 0; i < ARRAY_SIZE(regulators); i++) {
		rdev = devm_regulator_register(&pdev->dev, &regulators[i].desc,
					       &config);
		if (IS_ERR(rdev)) {
			dev_err(tps->dev, "failed to register %s regulator\n",
				pdev->name);
			return PTR_ERR(rdev);
		}
	}

	return 0;
}