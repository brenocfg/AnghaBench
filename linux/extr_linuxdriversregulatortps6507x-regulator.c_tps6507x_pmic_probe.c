#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tps_info {unsigned int defdcdc_default; int /*<<< orphan*/  table; int /*<<< orphan*/  table_len; int /*<<< orphan*/  name; } ;
struct tps6507x_reg_platform_data {unsigned int defdcdc_default; } ;
struct tps6507x_pmic {struct regulator_dev** rdev; TYPE_2__* desc; struct tps_info** info; struct tps6507x_dev* mfd; int /*<<< orphan*/  io_lock; } ;
struct tps6507x_dev {struct tps6507x_pmic* pmic; TYPE_4__* dev; } ;
struct tps6507x_board {struct regulator_init_data* tps6507x_pmic_init_data; } ;
struct regulator_init_data {struct tps6507x_reg_platform_data* driver_data; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  of_node; struct tps6507x_pmic* driver_data; struct regulator_init_data* init_data; TYPE_4__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct of_regulator_match {int /*<<< orphan*/  of_node; } ;
struct TYPE_8__ {scalar_t__ of_node; } ;
struct TYPE_7__ {int id; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; int /*<<< orphan*/  volt_table; int /*<<< orphan*/  n_voltages; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int TPS6507X_NUM_REGULATOR ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 struct tps6507x_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct tps6507x_board* dev_get_platdata (TYPE_4__*) ; 
 struct tps6507x_pmic* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,TYPE_2__*,struct regulator_config*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,unsigned int*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct tps6507x_dev*) ; 
 struct tps6507x_board* tps6507x_parse_dt_reg_data (struct platform_device*,struct of_regulator_match**) ; 
 int /*<<< orphan*/  tps6507x_pmic_ops ; 
 struct tps_info* tps6507x_pmic_regs ; 

__attribute__((used)) static int tps6507x_pmic_probe(struct platform_device *pdev)
{
	struct tps6507x_dev *tps6507x_dev = dev_get_drvdata(pdev->dev.parent);
	struct tps_info *info = &tps6507x_pmic_regs[0];
	struct regulator_config config = { };
	struct regulator_init_data *init_data;
	struct regulator_dev *rdev;
	struct tps6507x_pmic *tps;
	struct tps6507x_board *tps_board;
	struct of_regulator_match *tps6507x_reg_matches = NULL;
	int i;
	int error;
	unsigned int prop;

	/**
	 * tps_board points to pmic related constants
	 * coming from the board-evm file.
	 */

	tps_board = dev_get_platdata(tps6507x_dev->dev);
	if (IS_ENABLED(CONFIG_OF) && !tps_board &&
		tps6507x_dev->dev->of_node)
		tps_board = tps6507x_parse_dt_reg_data(pdev,
				&tps6507x_reg_matches);
	if (!tps_board)
		return -EINVAL;

	/**
	 * init_data points to array of regulator_init structures
	 * coming from the board-evm file.
	 */
	init_data = tps_board->tps6507x_pmic_init_data;
	if (!init_data)
		return -EINVAL;

	tps = devm_kzalloc(&pdev->dev, sizeof(*tps), GFP_KERNEL);
	if (!tps)
		return -ENOMEM;

	mutex_init(&tps->io_lock);

	/* common for all regulators */
	tps->mfd = tps6507x_dev;

	for (i = 0; i < TPS6507X_NUM_REGULATOR; i++, info++, init_data++) {
		/* Register the regulators */
		tps->info[i] = info;
		if (init_data->driver_data) {
			struct tps6507x_reg_platform_data *data =
					init_data->driver_data;
			tps->info[i]->defdcdc_default = data->defdcdc_default;
		}

		tps->desc[i].name = info->name;
		tps->desc[i].id = i;
		tps->desc[i].n_voltages = info->table_len;
		tps->desc[i].volt_table = info->table;
		tps->desc[i].ops = &tps6507x_pmic_ops;
		tps->desc[i].type = REGULATOR_VOLTAGE;
		tps->desc[i].owner = THIS_MODULE;

		config.dev = tps6507x_dev->dev;
		config.init_data = init_data;
		config.driver_data = tps;

		if (tps6507x_reg_matches) {
			error = of_property_read_u32(
				tps6507x_reg_matches[i].of_node,
					"ti,defdcdc_default", &prop);

			if (!error)
				tps->info[i]->defdcdc_default = prop;

			config.of_node = tps6507x_reg_matches[i].of_node;
		}

		rdev = devm_regulator_register(&pdev->dev, &tps->desc[i],
					       &config);
		if (IS_ERR(rdev)) {
			dev_err(tps6507x_dev->dev,
				"failed to register %s regulator\n",
				pdev->name);
			return PTR_ERR(rdev);
		}

		/* Save regulator for cleanup */
		tps->rdev[i] = rdev;
	}

	tps6507x_dev->pmic = tps;
	platform_set_drvdata(pdev, tps6507x_dev);

	return 0;
}