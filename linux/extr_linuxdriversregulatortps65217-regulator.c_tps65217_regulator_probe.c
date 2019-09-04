#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct tps65217_board {int /*<<< orphan*/ * tps65217_init_data; } ;
struct tps65217 {unsigned int* strobes; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  regmap; struct tps65217* driver_data; int /*<<< orphan*/  init_data; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; TYPE_2__ dev; } ;
struct TYPE_5__ {unsigned int bypass_mask; int /*<<< orphan*/  bypass_reg; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int TPS65217_NUM_REGULATOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct tps65217* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct tps65217_board* dev_get_platdata (int /*<<< orphan*/ ) ; 
 unsigned int* devm_kcalloc (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_2__*,TYPE_1__*,struct regulator_config*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tps65217*) ; 
 TYPE_1__* regulators ; 
 int tps65217_reg_read (struct tps65217*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int tps65217_regulator_probe(struct platform_device *pdev)
{
	struct tps65217 *tps = dev_get_drvdata(pdev->dev.parent);
	struct tps65217_board *pdata = dev_get_platdata(tps->dev);
	struct regulator_dev *rdev;
	struct regulator_config config = { };
	int i, ret;
	unsigned int val;

	/* Allocate memory for strobes */
	tps->strobes = devm_kcalloc(&pdev->dev,
				    TPS65217_NUM_REGULATOR, sizeof(u8),
				    GFP_KERNEL);
	if (!tps->strobes)
		return -ENOMEM;

	platform_set_drvdata(pdev, tps);

	for (i = 0; i < TPS65217_NUM_REGULATOR; i++) {
		/* Register the regulators */
		config.dev = tps->dev;
		if (pdata)
			config.init_data = pdata->tps65217_init_data[i];
		config.driver_data = tps;
		config.regmap = tps->regmap;

		rdev = devm_regulator_register(&pdev->dev, &regulators[i],
					       &config);
		if (IS_ERR(rdev)) {
			dev_err(tps->dev, "failed to register %s regulator\n",
				pdev->name);
			return PTR_ERR(rdev);
		}

		/* Store default strobe info */
		ret = tps65217_reg_read(tps, regulators[i].bypass_reg, &val);
		tps->strobes[i] = val & regulators[i].bypass_mask;
	}

	return 0;
}