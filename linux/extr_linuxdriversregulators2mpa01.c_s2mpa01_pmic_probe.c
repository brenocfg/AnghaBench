#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct sec_pmic_dev {int /*<<< orphan*/  regmap_pmic; TYPE_7__* dev; } ;
struct sec_platform_data {TYPE_1__* regulators; } ;
struct s2mpa01_info {struct of_regulator_match* rdata; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  of_node; int /*<<< orphan*/  init_data; struct s2mpa01_info* driver_data; int /*<<< orphan*/  regmap; TYPE_3__* dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_3__ dev; } ;
struct of_regulator_match {int /*<<< orphan*/  of_node; int /*<<< orphan*/  init_data; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;
struct TYPE_12__ {scalar_t__ of_node; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  initdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int S2MPA01_REGULATOR_CNT ; 
 int S2MPA01_REGULATOR_MAX ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 struct sec_pmic_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct sec_platform_data* dev_get_platdata (TYPE_7__*) ; 
 struct s2mpa01_info* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_3__*,TYPE_2__*,struct regulator_config*) ; 
 struct device_node* of_get_child_by_name (scalar_t__,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_regulator_match (TYPE_3__*,struct device_node*,struct of_regulator_match*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct s2mpa01_info*) ; 
 TYPE_2__* regulators ; 

__attribute__((used)) static int s2mpa01_pmic_probe(struct platform_device *pdev)
{
	struct sec_pmic_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	struct sec_platform_data *pdata = dev_get_platdata(iodev->dev);
	struct device_node *reg_np = NULL;
	struct regulator_config config = { };
	struct of_regulator_match *rdata;
	struct s2mpa01_info *s2mpa01;
	int i;

	s2mpa01 = devm_kzalloc(&pdev->dev, sizeof(*s2mpa01), GFP_KERNEL);
	if (!s2mpa01)
		return -ENOMEM;

	rdata = s2mpa01->rdata;
	for (i = 0; i < S2MPA01_REGULATOR_CNT; i++)
		rdata[i].name = regulators[i].name;

	if (iodev->dev->of_node) {
		reg_np = of_get_child_by_name(iodev->dev->of_node,
							"regulators");
		if (!reg_np) {
			dev_err(&pdev->dev,
				"could not find regulators sub-node\n");
			return -EINVAL;
		}

		of_regulator_match(&pdev->dev, reg_np, rdata,
						S2MPA01_REGULATOR_MAX);
		of_node_put(reg_np);
	}

	platform_set_drvdata(pdev, s2mpa01);

	config.dev = &pdev->dev;
	config.regmap = iodev->regmap_pmic;
	config.driver_data = s2mpa01;

	for (i = 0; i < S2MPA01_REGULATOR_MAX; i++) {
		struct regulator_dev *rdev;
		if (pdata)
			config.init_data = pdata->regulators[i].initdata;
		else
			config.init_data = rdata[i].init_data;

		if (reg_np)
			config.of_node = rdata[i].of_node;

		rdev = devm_regulator_register(&pdev->dev,
						&regulators[i], &config);
		if (IS_ERR(rdev)) {
			dev_err(&pdev->dev, "regulator init failed for %d\n",
				i);
			return PTR_ERR(rdev);
		}
	}

	return 0;
}