#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct tps65218 {unsigned int* strobes; int /*<<< orphan*/  regmap; TYPE_5__* dev; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  regmap; struct tps65218* driver_data; TYPE_2__* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; TYPE_2__ dev; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_7__ {unsigned int bypass_mask; int /*<<< orphan*/  bypass_reg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  TPS65218_NUM_REGULATOR ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*,int /*<<< orphan*/ ) ; 
 struct tps65218* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 unsigned int* devm_kcalloc (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_2__*,TYPE_1__*,struct regulator_config*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 TYPE_1__* regulators ; 

__attribute__((used)) static int tps65218_regulator_probe(struct platform_device *pdev)
{
	struct tps65218 *tps = dev_get_drvdata(pdev->dev.parent);
	struct regulator_dev *rdev;
	struct regulator_config config = { };
	int i, ret;
	unsigned int val;

	config.dev = &pdev->dev;
	config.dev->of_node = tps->dev->of_node;
	config.driver_data = tps;
	config.regmap = tps->regmap;

	/* Allocate memory for strobes */
	tps->strobes = devm_kcalloc(&pdev->dev,
				    TPS65218_NUM_REGULATOR, sizeof(u8),
				    GFP_KERNEL);
	if (!tps->strobes)
		return -ENOMEM;

	for (i = 0; i < ARRAY_SIZE(regulators); i++) {
		rdev = devm_regulator_register(&pdev->dev, &regulators[i],
					       &config);
		if (IS_ERR(rdev)) {
			dev_err(tps->dev, "failed to register %s regulator\n",
				pdev->name);
			return PTR_ERR(rdev);
		}

		ret = regmap_read(tps->regmap, regulators[i].bypass_reg, &val);
		if (ret)
			return ret;

		tps->strobes[i] = val & regulators[i].bypass_mask;
	}

	return 0;
}