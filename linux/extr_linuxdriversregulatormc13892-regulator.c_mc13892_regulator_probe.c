#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct regulator_ops {int dummy; } ;
struct regulator_init_data {int dummy; } ;
struct regulator_desc {int /*<<< orphan*/  name; TYPE_2__* ops; } ;
struct regulator_config {struct device_node* of_node; struct mc13xxx_regulator_priv* driver_data; struct regulator_init_data* init_data; TYPE_7__* dev; } ;
struct TYPE_15__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_7__ dev; } ;
struct mc13xxx_regulator_priv {int num_regulators; int /*<<< orphan*/ * regulators; struct mc13xxx* mc13xxx; TYPE_4__* mc13xxx_regulators; } ;
struct mc13xxx_regulator_platform_data {int num_regulators; TYPE_1__* regulators; } ;
struct mc13xxx_regulator_init_data {int id; struct device_node* node; struct regulator_init_data* init_data; } ;
struct mc13xxx {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_14__ {struct regulator_desc desc; } ;
struct TYPE_13__ {int /*<<< orphan*/  get_mode; int /*<<< orphan*/  set_mode; } ;
struct TYPE_12__ {int id; struct regulator_init_data* init_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_4__*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MC13892_REVISION ; 
 int /*<<< orphan*/  MC13892_SWITCHERS4 ; 
 int MC13892_SWITCHERS4_SW1MODE_AUTO ; 
 int MC13892_SWITCHERS4_SW1MODE_M ; 
 int MC13892_SWITCHERS4_SW2MODE_AUTO ; 
 int MC13892_SWITCHERS4_SW2MODE_M ; 
 int /*<<< orphan*/  MC13892_SWITCHERS5 ; 
 int MC13892_SWITCHERS5_SW3MODE_AUTO ; 
 int MC13892_SWITCHERS5_SW3MODE_M ; 
 int MC13892_SWITCHERS5_SW4MODE_AUTO ; 
 int MC13892_SWITCHERS5_SW4MODE_M ; 
 size_t MC13892_VCAM ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_7__*,char*,int /*<<< orphan*/ ) ; 
 struct mc13xxx* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct mc13xxx_regulator_platform_data* dev_get_platdata (TYPE_7__*) ; 
 struct mc13xxx_regulator_priv* devm_kzalloc (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_register (TYPE_7__*,struct regulator_desc*,struct regulator_config*) ; 
 TYPE_4__* mc13892_regulators ; 
 int /*<<< orphan*/  mc13892_vcam_get_mode ; 
 TYPE_2__ mc13892_vcam_ops ; 
 int /*<<< orphan*/  mc13892_vcam_set_mode ; 
 int mc13xxx_get_num_regulators_dt (struct platform_device*) ; 
 int /*<<< orphan*/  mc13xxx_lock (struct mc13xxx*) ; 
 struct mc13xxx_regulator_init_data* mc13xxx_parse_regulators_dt (struct platform_device*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int mc13xxx_reg_read (struct mc13xxx*,int /*<<< orphan*/ ,int*) ; 
 int mc13xxx_reg_rmw (struct mc13xxx*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mc13xxx_unlock (struct mc13xxx*) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mc13xxx_regulator_priv*) ; 
 int /*<<< orphan*/  regulators ; 
 int /*<<< orphan*/  struct_size (struct mc13xxx_regulator_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mc13892_regulator_probe(struct platform_device *pdev)
{
	struct mc13xxx_regulator_priv *priv;
	struct mc13xxx *mc13892 = dev_get_drvdata(pdev->dev.parent);
	struct mc13xxx_regulator_platform_data *pdata =
		dev_get_platdata(&pdev->dev);
	struct mc13xxx_regulator_init_data *mc13xxx_data;
	struct regulator_config config = { };
	int i, ret;
	int num_regulators = 0;
	u32 val;

	num_regulators = mc13xxx_get_num_regulators_dt(pdev);

	if (num_regulators <= 0 && pdata)
		num_regulators = pdata->num_regulators;
	if (num_regulators <= 0)
		return -EINVAL;

	priv = devm_kzalloc(&pdev->dev,
			    struct_size(priv, regulators, num_regulators),
			    GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->num_regulators = num_regulators;
	priv->mc13xxx_regulators = mc13892_regulators;
	priv->mc13xxx = mc13892;
	platform_set_drvdata(pdev, priv);

	mc13xxx_lock(mc13892);
	ret = mc13xxx_reg_read(mc13892, MC13892_REVISION, &val);
	if (ret)
		goto err_unlock;

	/* enable switch auto mode (on 2.0A silicon only) */
	if ((val & 0x0000FFFF) == 0x45d0) {
		ret = mc13xxx_reg_rmw(mc13892, MC13892_SWITCHERS4,
			MC13892_SWITCHERS4_SW1MODE_M |
			MC13892_SWITCHERS4_SW2MODE_M,
			MC13892_SWITCHERS4_SW1MODE_AUTO |
			MC13892_SWITCHERS4_SW2MODE_AUTO);
		if (ret)
			goto err_unlock;

		ret = mc13xxx_reg_rmw(mc13892, MC13892_SWITCHERS5,
			MC13892_SWITCHERS5_SW3MODE_M |
			MC13892_SWITCHERS5_SW4MODE_M,
			MC13892_SWITCHERS5_SW3MODE_AUTO |
			MC13892_SWITCHERS5_SW4MODE_AUTO);
		if (ret)
			goto err_unlock;
	}
	mc13xxx_unlock(mc13892);

	/* update mc13892_vcam ops */
	memcpy(&mc13892_vcam_ops, mc13892_regulators[MC13892_VCAM].desc.ops,
						sizeof(struct regulator_ops));
	mc13892_vcam_ops.set_mode = mc13892_vcam_set_mode,
	mc13892_vcam_ops.get_mode = mc13892_vcam_get_mode,
	mc13892_regulators[MC13892_VCAM].desc.ops = &mc13892_vcam_ops;

	mc13xxx_data = mc13xxx_parse_regulators_dt(pdev, mc13892_regulators,
					ARRAY_SIZE(mc13892_regulators));

	for (i = 0; i < priv->num_regulators; i++) {
		struct regulator_init_data *init_data;
		struct regulator_desc *desc;
		struct device_node *node = NULL;
		int id;

		if (mc13xxx_data) {
			id = mc13xxx_data[i].id;
			init_data = mc13xxx_data[i].init_data;
			node = mc13xxx_data[i].node;
		} else {
			id = pdata->regulators[i].id;
			init_data = pdata->regulators[i].init_data;
		}
		desc = &mc13892_regulators[id].desc;

		config.dev = &pdev->dev;
		config.init_data = init_data;
		config.driver_data = priv;
		config.of_node = node;

		priv->regulators[i] = devm_regulator_register(&pdev->dev, desc,
							      &config);
		if (IS_ERR(priv->regulators[i])) {
			dev_err(&pdev->dev, "failed to register regulator %s\n",
				mc13892_regulators[i].desc.name);
			return PTR_ERR(priv->regulators[i]);
		}
	}

	return 0;

err_unlock:
	mc13xxx_unlock(mc13892);
	return ret;
}