#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator_desc {int /*<<< orphan*/  enable_reg; } ;
struct regulator_config {int /*<<< orphan*/  of_node; TYPE_2__* init_data; int /*<<< orphan*/  regmap; struct arizona_micsupp* driver_data; int /*<<< orphan*/  dev; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct arizona_micsupp_pdata {TYPE_2__* init_data; } ;
struct TYPE_4__ {TYPE_1__* consumer_supplies; } ;
struct TYPE_3__ {char* supply; int /*<<< orphan*/  dev_name; } ;
struct arizona_micsupp {int /*<<< orphan*/  dev; int /*<<< orphan*/  regulator; int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  regmap; TYPE_2__ init_data; TYPE_1__ supply; int /*<<< orphan*/  check_cp_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_CPMIC_BYPASS ; 
 int /*<<< orphan*/  CONFIG_OF ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arizona_micsupp_check_cp ; 
 int arizona_micsupp_of_get_pdata (struct arizona_micsupp_pdata*,struct regulator_config*,struct regulator_desc const*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_get_platdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_register (int /*<<< orphan*/ *,struct regulator_desc const*,struct regulator_config*) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct arizona_micsupp*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arizona_micsupp_common_init(struct platform_device *pdev,
				       struct arizona_micsupp *micsupp,
				       const struct regulator_desc *desc,
				       struct arizona_micsupp_pdata *pdata)
{
	struct regulator_config config = { };
	int ret;

	INIT_WORK(&micsupp->check_cp_work, arizona_micsupp_check_cp);

	micsupp->init_data.consumer_supplies = &micsupp->supply;
	micsupp->supply.supply = "MICVDD";
	micsupp->supply.dev_name = dev_name(micsupp->dev);
	micsupp->enable_reg = desc->enable_reg;

	config.dev = micsupp->dev;
	config.driver_data = micsupp;
	config.regmap = micsupp->regmap;

	if (IS_ENABLED(CONFIG_OF)) {
		if (!dev_get_platdata(micsupp->dev)) {
			ret = arizona_micsupp_of_get_pdata(pdata, &config,
							   desc);
			if (ret < 0)
				return ret;
		}
	}

	if (pdata->init_data)
		config.init_data = pdata->init_data;
	else
		config.init_data = &micsupp->init_data;

	/* Default to regulated mode */
	regmap_update_bits(micsupp->regmap, micsupp->enable_reg,
			   ARIZONA_CPMIC_BYPASS, 0);

	micsupp->regulator = devm_regulator_register(&pdev->dev,
						     desc,
						     &config);

	of_node_put(config.of_node);

	if (IS_ERR(micsupp->regulator)) {
		ret = PTR_ERR(micsupp->regulator);
		dev_err(micsupp->dev, "Failed to register mic supply: %d\n",
			ret);
		return ret;
	}

	platform_set_drvdata(pdev, micsupp);

	return 0;
}