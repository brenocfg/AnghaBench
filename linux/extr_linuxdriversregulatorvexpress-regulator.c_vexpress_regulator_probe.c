#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int continuous_voltage_range; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct vexpress_regulator {int /*<<< orphan*/  regdev; TYPE_3__ desc; int /*<<< orphan*/  regmap; } ;
struct TYPE_9__ {scalar_t__ max_uV; scalar_t__ min_uV; scalar_t__ apply_uV; } ;
struct regulator_init_data {TYPE_1__ constraints; } ;
struct regulator_config {int /*<<< orphan*/  of_node; struct vexpress_regulator* driver_data; struct regulator_init_data* init_data; TYPE_2__* dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 struct vexpress_regulator* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_vexpress_config (TYPE_2__*) ; 
 int /*<<< orphan*/  devm_regulator_register (TYPE_2__*,TYPE_3__*,struct regulator_config*) ; 
 struct regulator_init_data* of_get_regulator_init_data (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct vexpress_regulator*) ; 
 int /*<<< orphan*/  vexpress_regulator_ops ; 
 int /*<<< orphan*/  vexpress_regulator_ops_ro ; 

__attribute__((used)) static int vexpress_regulator_probe(struct platform_device *pdev)
{
	struct vexpress_regulator *reg;
	struct regulator_init_data *init_data;
	struct regulator_config config = { };

	reg = devm_kzalloc(&pdev->dev, sizeof(*reg), GFP_KERNEL);
	if (!reg)
		return -ENOMEM;

	reg->regmap = devm_regmap_init_vexpress_config(&pdev->dev);
	if (IS_ERR(reg->regmap))
		return PTR_ERR(reg->regmap);

	reg->desc.name = dev_name(&pdev->dev);
	reg->desc.type = REGULATOR_VOLTAGE;
	reg->desc.owner = THIS_MODULE;
	reg->desc.continuous_voltage_range = true;

	init_data = of_get_regulator_init_data(&pdev->dev, pdev->dev.of_node,
					       &reg->desc);
	if (!init_data)
		return -EINVAL;

	init_data->constraints.apply_uV = 0;
	if (init_data->constraints.min_uV && init_data->constraints.max_uV)
		reg->desc.ops = &vexpress_regulator_ops;
	else
		reg->desc.ops = &vexpress_regulator_ops_ro;

	config.dev = &pdev->dev;
	config.init_data = init_data;
	config.driver_data = reg;
	config.of_node = pdev->dev.of_node;

	reg->regdev = devm_regulator_register(&pdev->dev, &reg->desc, &config);
	if (IS_ERR(reg->regdev))
		return PTR_ERR(reg->regdev);

	platform_set_drvdata(pdev, reg);

	return 0;
}