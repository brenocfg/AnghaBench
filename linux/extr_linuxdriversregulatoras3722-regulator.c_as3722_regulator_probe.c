#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct regulator_ops {int dummy; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  of_node; int /*<<< orphan*/  init_data; int /*<<< orphan*/  regmap; struct as3722_regulators* driver_data; TYPE_1__* dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct as3722_regulators {struct regulator_dev** rdevs; TYPE_2__* desc; struct as3722_regulator_config_data* reg_config_data; struct as3722* as3722; TYPE_1__* dev; } ;
struct as3722_regulator_config_data {scalar_t__ ext_control; int /*<<< orphan*/  reg_init; int /*<<< orphan*/  enable_tracking; } ;
struct as3722 {int /*<<< orphan*/  regmap; } ;
struct TYPE_10__ {int /*<<< orphan*/  vsel_mask; int /*<<< orphan*/  vsel_reg; int /*<<< orphan*/  enable_mask; int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  n_voltages; int /*<<< orphan*/  regulator_id; int /*<<< orphan*/  sname; int /*<<< orphan*/  name; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_8__ {int min_uV; int uV_step; int linear_min_sel; int enable_time; struct regulator_ops const* ops; void* n_linear_ranges; void* linear_ranges; int /*<<< orphan*/  n_voltages; void* bypass_val_off; void* bypass_val_on; int /*<<< orphan*/  bypass_mask; int /*<<< orphan*/  bypass_reg; int /*<<< orphan*/  vsel_mask; int /*<<< orphan*/  vsel_reg; int /*<<< orphan*/  enable_mask; int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/  id; int /*<<< orphan*/  supply_name; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  AS3722_LDO3_MODE_PMOS_TRACKING ; 
 int /*<<< orphan*/  AS3722_LDO6_VOLTAGE_REG ; 
 void* AS3722_LDO6_VSEL_BYPASS ; 
 int /*<<< orphan*/  AS3722_LDO_VSEL_MASK ; 
#define  AS3722_REGULATOR_ID_LDO0 137 
#define  AS3722_REGULATOR_ID_LDO3 136 
#define  AS3722_REGULATOR_ID_LDO6 135 
 int AS3722_REGULATOR_ID_MAX ; 
#define  AS3722_REGULATOR_ID_SD0 134 
#define  AS3722_REGULATOR_ID_SD1 133 
#define  AS3722_REGULATOR_ID_SD2 132 
#define  AS3722_REGULATOR_ID_SD3 131 
#define  AS3722_REGULATOR_ID_SD4 130 
#define  AS3722_REGULATOR_ID_SD5 129 
#define  AS3722_REGULATOR_ID_SD6 128 
 int /*<<< orphan*/  AS3722_SD0_VSEL_LOW_VOL_MAX ; 
 int /*<<< orphan*/  AS3722_SD0_VSEL_MAX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int as3722_extreg_init (struct as3722_regulators*,int,scalar_t__) ; 
 int as3722_get_regulator_dt_data (struct platform_device*,struct as3722_regulators*) ; 
 struct regulator_ops as3722_ldo0_extcntrl_ops ; 
 struct regulator_ops as3722_ldo0_ops ; 
 struct regulator_ops as3722_ldo3_extcntrl_ops ; 
 struct regulator_ops as3722_ldo3_ops ; 
 int as3722_ldo3_set_tracking_mode (struct as3722_regulators*,int,int /*<<< orphan*/ ) ; 
 struct regulator_ops as3722_ldo6_extcntrl_ops ; 
 struct regulator_ops as3722_ldo6_ops ; 
 struct regulator_ops as3722_ldo_extcntrl_ops ; 
 struct regulator_ops as3722_ldo_ops ; 
 void* as3722_ldo_ranges ; 
 TYPE_6__* as3722_reg_lookup ; 
 TYPE_5__* as3722_regulator_matches ; 
 struct regulator_ops as3722_sd016_extcntrl_ops ; 
 struct regulator_ops as3722_sd016_ops ; 
 int /*<<< orphan*/  as3722_sd0_is_low_voltage (struct as3722_regulators*) ; 
 struct regulator_ops as3722_sd2345_extcntrl_ops ; 
 struct regulator_ops as3722_sd2345_ops ; 
 void* as3722_sd2345_ranges ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int,...) ; 
 struct as3722* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct as3722_regulators* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,TYPE_2__*,struct regulator_config*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct as3722_regulators*) ; 
 int regulator_enable_regmap (struct regulator_dev*) ; 

__attribute__((used)) static int as3722_regulator_probe(struct platform_device *pdev)
{
	struct as3722 *as3722 = dev_get_drvdata(pdev->dev.parent);
	struct as3722_regulators *as3722_regs;
	struct as3722_regulator_config_data *reg_config;
	struct regulator_dev *rdev;
	struct regulator_config config = { };
	const struct regulator_ops *ops;
	int id;
	int ret;

	as3722_regs = devm_kzalloc(&pdev->dev, sizeof(*as3722_regs),
				GFP_KERNEL);
	if (!as3722_regs)
		return -ENOMEM;

	as3722_regs->dev = &pdev->dev;
	as3722_regs->as3722 = as3722;
	platform_set_drvdata(pdev, as3722_regs);

	ret = as3722_get_regulator_dt_data(pdev, as3722_regs);
	if (ret < 0)
		return ret;

	config.dev = &pdev->dev;
	config.driver_data = as3722_regs;
	config.regmap = as3722->regmap;

	for (id = 0; id < AS3722_REGULATOR_ID_MAX; id++) {
		reg_config = &as3722_regs->reg_config_data[id];

		as3722_regs->desc[id].name = as3722_reg_lookup[id].name;
		as3722_regs->desc[id].supply_name = as3722_reg_lookup[id].sname;
		as3722_regs->desc[id].id = as3722_reg_lookup[id].regulator_id;
		as3722_regs->desc[id].n_voltages =
					as3722_reg_lookup[id].n_voltages;
		as3722_regs->desc[id].type = REGULATOR_VOLTAGE;
		as3722_regs->desc[id].owner = THIS_MODULE;
		as3722_regs->desc[id].enable_reg =
					as3722_reg_lookup[id].enable_reg;
		as3722_regs->desc[id].enable_mask =
					as3722_reg_lookup[id].enable_mask;
		as3722_regs->desc[id].vsel_reg = as3722_reg_lookup[id].vsel_reg;
		as3722_regs->desc[id].vsel_mask =
					as3722_reg_lookup[id].vsel_mask;
		switch (id) {
		case AS3722_REGULATOR_ID_LDO0:
			if (reg_config->ext_control)
				ops = &as3722_ldo0_extcntrl_ops;
			else
				ops = &as3722_ldo0_ops;
			as3722_regs->desc[id].min_uV = 825000;
			as3722_regs->desc[id].uV_step = 25000;
			as3722_regs->desc[id].linear_min_sel = 1;
			as3722_regs->desc[id].enable_time = 500;
			break;
		case AS3722_REGULATOR_ID_LDO3:
			if (reg_config->ext_control)
				ops = &as3722_ldo3_extcntrl_ops;
			else
				ops = &as3722_ldo3_ops;
			as3722_regs->desc[id].min_uV = 620000;
			as3722_regs->desc[id].uV_step = 20000;
			as3722_regs->desc[id].linear_min_sel = 1;
			as3722_regs->desc[id].enable_time = 500;
			if (reg_config->enable_tracking) {
				ret = as3722_ldo3_set_tracking_mode(as3722_regs,
					id, AS3722_LDO3_MODE_PMOS_TRACKING);
				if (ret < 0) {
					dev_err(&pdev->dev,
						"LDO3 tracking failed: %d\n",
						ret);
					return ret;
				}
			}
			break;
		case AS3722_REGULATOR_ID_LDO6:
			if (reg_config->ext_control)
				ops = &as3722_ldo6_extcntrl_ops;
			else
				ops = &as3722_ldo6_ops;
			as3722_regs->desc[id].enable_time = 500;
			as3722_regs->desc[id].bypass_reg =
						AS3722_LDO6_VOLTAGE_REG;
			as3722_regs->desc[id].bypass_mask =
						AS3722_LDO_VSEL_MASK;
			as3722_regs->desc[id].bypass_val_on =
						AS3722_LDO6_VSEL_BYPASS;
			as3722_regs->desc[id].bypass_val_off =
						AS3722_LDO6_VSEL_BYPASS;
			as3722_regs->desc[id].linear_ranges = as3722_ldo_ranges;
			as3722_regs->desc[id].n_linear_ranges =
						ARRAY_SIZE(as3722_ldo_ranges);
			break;
		case AS3722_REGULATOR_ID_SD0:
		case AS3722_REGULATOR_ID_SD1:
		case AS3722_REGULATOR_ID_SD6:
			if (reg_config->ext_control)
				ops = &as3722_sd016_extcntrl_ops;
			else
				ops = &as3722_sd016_ops;
			if (id == AS3722_REGULATOR_ID_SD0 &&
			    as3722_sd0_is_low_voltage(as3722_regs)) {
				as3722_regs->desc[id].n_voltages =
					AS3722_SD0_VSEL_LOW_VOL_MAX + 1;
				as3722_regs->desc[id].min_uV = 410000;
			} else {
				as3722_regs->desc[id].n_voltages =
					AS3722_SD0_VSEL_MAX + 1,
				as3722_regs->desc[id].min_uV = 610000;
			}
			as3722_regs->desc[id].uV_step = 10000;
			as3722_regs->desc[id].linear_min_sel = 1;
			as3722_regs->desc[id].enable_time = 600;
			break;
		case AS3722_REGULATOR_ID_SD2:
		case AS3722_REGULATOR_ID_SD3:
		case AS3722_REGULATOR_ID_SD4:
		case AS3722_REGULATOR_ID_SD5:
			if (reg_config->ext_control)
				ops = &as3722_sd2345_extcntrl_ops;
			else
				ops = &as3722_sd2345_ops;
			as3722_regs->desc[id].linear_ranges =
						as3722_sd2345_ranges;
			as3722_regs->desc[id].n_linear_ranges =
					ARRAY_SIZE(as3722_sd2345_ranges);
			break;
		default:
			if (reg_config->ext_control)
				ops = &as3722_ldo_extcntrl_ops;
			else
				ops = &as3722_ldo_ops;
			as3722_regs->desc[id].enable_time = 500;
			as3722_regs->desc[id].linear_ranges = as3722_ldo_ranges;
			as3722_regs->desc[id].n_linear_ranges =
						ARRAY_SIZE(as3722_ldo_ranges);
			break;
		}
		as3722_regs->desc[id].ops = ops;
		config.init_data = reg_config->reg_init;
		config.of_node = as3722_regulator_matches[id].of_node;
		rdev = devm_regulator_register(&pdev->dev,
					&as3722_regs->desc[id], &config);
		if (IS_ERR(rdev)) {
			ret = PTR_ERR(rdev);
			dev_err(&pdev->dev, "regulator %d register failed %d\n",
				id, ret);
			return ret;
		}

		as3722_regs->rdevs[id] = rdev;
		if (reg_config->ext_control) {
			ret = regulator_enable_regmap(rdev);
			if (ret < 0) {
				dev_err(&pdev->dev,
					"Regulator %d enable failed: %d\n",
					id, ret);
				return ret;
			}
			ret = as3722_extreg_init(as3722_regs, id,
					reg_config->ext_control);
			if (ret < 0) {
				dev_err(&pdev->dev,
					"AS3722 ext control failed: %d", ret);
				return ret;
			}
		}
	}
	return 0;
}