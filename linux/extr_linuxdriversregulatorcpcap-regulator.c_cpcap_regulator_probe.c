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
struct regulator_init_data {void* driver_data; struct regulator_init_data* init_data; scalar_t__ regmap; TYPE_1__* dev; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {void* driver_data; struct regulator_config* init_data; scalar_t__ regmap; TYPE_1__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct of_device_id {struct cpcap_regulator* data; } ;
struct TYPE_7__ {scalar_t__ volt_table; int /*<<< orphan*/  name; } ;
struct cpcap_regulator {TYPE_3__ rdesc; } ;
struct cpcap_ddata {struct cpcap_regulator* soc; scalar_t__ reg; TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  int /*<<< orphan*/  config ;

/* Variables and functions */
 int CPCAP_NR_REGULATORS ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  cpcap_regulator_id_table ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 scalar_t__ dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cpcap_ddata* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,TYPE_3__*,struct regulator_init_data*) ; 
 int /*<<< orphan*/  memset (struct regulator_init_data*,int /*<<< orphan*/ ,int) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_match_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct cpcap_ddata*) ; 
 scalar_t__ unknown_val_tbl ; 

__attribute__((used)) static int cpcap_regulator_probe(struct platform_device *pdev)
{
	struct cpcap_ddata *ddata;
	const struct of_device_id *match;
	struct regulator_config config;
	struct regulator_init_data init_data;
	int i;

	match = of_match_device(of_match_ptr(cpcap_regulator_id_table),
				&pdev->dev);
	if (!match)
		return -EINVAL;

	if (!match->data) {
		dev_err(&pdev->dev, "no configuration data found\n");

		return -ENODEV;
	}

	ddata = devm_kzalloc(&pdev->dev, sizeof(*ddata), GFP_KERNEL);
	if (!ddata)
		return -ENOMEM;

	ddata->reg = dev_get_regmap(pdev->dev.parent, NULL);
	if (!ddata->reg)
		return -ENODEV;

	ddata->dev = &pdev->dev;
	ddata->soc = match->data;
	platform_set_drvdata(pdev, ddata);

	memset(&config, 0, sizeof(config));
	memset(&init_data, 0, sizeof(init_data));
	config.dev = &pdev->dev;
	config.regmap = ddata->reg;
	config.init_data = &init_data;

	for (i = 0; i < CPCAP_NR_REGULATORS; i++) {
		const struct cpcap_regulator *regulator = &ddata->soc[i];
		struct regulator_dev *rdev;

		if (!regulator->rdesc.name)
			break;

		if (regulator->rdesc.volt_table == unknown_val_tbl)
			continue;

		config.driver_data = (void *)regulator;
		rdev = devm_regulator_register(&pdev->dev,
					       &regulator->rdesc,
					       &config);
		if (IS_ERR(rdev)) {
			dev_err(&pdev->dev, "failed to register regulator %s\n",
				regulator->rdesc.name);

			return PTR_ERR(rdev);
		}
	}

	return 0;
}