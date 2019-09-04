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
struct regulator_dev {int dummy; } ;
struct regulator_desc {int name; } ;
struct regulator_config {int /*<<< orphan*/  regmap; struct bd71837_pmic* driver_data; int /*<<< orphan*/  dev; int /*<<< orphan*/  member_0; } ;
struct reg_init {int mask; int /*<<< orphan*/  reg; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct bd71837_pmic {struct regulator_dev** rdev; struct platform_device* pdev; TYPE_3__* mfd; struct regulator_desc* descs; } ;
struct TYPE_7__ {int /*<<< orphan*/  regmap; TYPE_1__* dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct reg_init*) ; 
 int BD71837_BUCK_SEL ; 
 int BD71837_LDO_SEL ; 
 int /*<<< orphan*/  BD71837_REG_BUCK1_CTRL ; 
 int /*<<< orphan*/  BD71837_REG_BUCK2_CTRL ; 
 int /*<<< orphan*/  BD71837_REG_BUCK3_CTRL ; 
 int /*<<< orphan*/  BD71837_REG_BUCK4_CTRL ; 
 int /*<<< orphan*/  BD71837_REG_BUCK5_CTRL ; 
 int /*<<< orphan*/  BD71837_REG_BUCK6_CTRL ; 
 int /*<<< orphan*/  BD71837_REG_BUCK7_CTRL ; 
 int /*<<< orphan*/  BD71837_REG_BUCK8_CTRL ; 
 int /*<<< orphan*/  BD71837_REG_LDO1_VOLT ; 
 int /*<<< orphan*/  BD71837_REG_LDO2_VOLT ; 
 int /*<<< orphan*/  BD71837_REG_LDO3_VOLT ; 
 int /*<<< orphan*/  BD71837_REG_LDO4_VOLT ; 
 int /*<<< orphan*/  BD71837_REG_LDO5_VOLT ; 
 int /*<<< orphan*/  BD71837_REG_LDO6_VOLT ; 
 int /*<<< orphan*/  BD71837_REG_LDO7_VOLT ; 
 int /*<<< orphan*/  BD71837_REG_REGLOCK ; 
 int BD718XX_LDO5_VRMON80 ; 
 int BD718XX_LDO6_VRMON80 ; 
 int /*<<< orphan*/  BD718XX_REG_MVRFLTMASK2 ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int REGLOCK_PWRSEQ ; 
 int REGLOCK_VREG ; 
 int /*<<< orphan*/  bd71837_regulators ; 
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 TYPE_3__* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct bd71837_pmic* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (TYPE_1__*,struct regulator_desc*,struct regulator_config*) ; 
 int /*<<< orphan*/  memcpy (struct regulator_desc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct bd71837_pmic*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int bd71837_probe(struct platform_device *pdev)
{
	struct bd71837_pmic *pmic;
	struct regulator_config config = { 0 };
	struct reg_init pmic_regulator_inits[] = {
		{
			.reg = BD71837_REG_BUCK1_CTRL,
			.mask = BD71837_BUCK_SEL,
		}, {
			.reg = BD71837_REG_BUCK2_CTRL,
			.mask = BD71837_BUCK_SEL,
		}, {
			.reg = BD71837_REG_BUCK3_CTRL,
			.mask = BD71837_BUCK_SEL,
		}, {
			.reg = BD71837_REG_BUCK4_CTRL,
			.mask = BD71837_BUCK_SEL,
		}, {
			.reg = BD71837_REG_BUCK5_CTRL,
			.mask = BD71837_BUCK_SEL,
		}, {
			.reg = BD71837_REG_BUCK6_CTRL,
			.mask = BD71837_BUCK_SEL,
		}, {
			.reg = BD71837_REG_BUCK7_CTRL,
			.mask = BD71837_BUCK_SEL,
		}, {
			.reg = BD71837_REG_BUCK8_CTRL,
			.mask = BD71837_BUCK_SEL,
		}, {
			.reg = BD71837_REG_LDO1_VOLT,
			.mask = BD71837_LDO_SEL,
		}, {
			.reg = BD71837_REG_LDO2_VOLT,
			.mask = BD71837_LDO_SEL,
		}, {
			.reg = BD71837_REG_LDO3_VOLT,
			.mask = BD71837_LDO_SEL,
		}, {
			.reg = BD71837_REG_LDO4_VOLT,
			.mask = BD71837_LDO_SEL,
		}, {
			.reg = BD71837_REG_LDO5_VOLT,
			.mask = BD71837_LDO_SEL,
		}, {
			.reg = BD71837_REG_LDO6_VOLT,
			.mask = BD71837_LDO_SEL,
		}, {
			.reg = BD71837_REG_LDO7_VOLT,
			.mask = BD71837_LDO_SEL,
		}
	};

	int i, err;

	pmic = devm_kzalloc(&pdev->dev, sizeof(*pmic), GFP_KERNEL);
	if (!pmic)
		return -ENOMEM;

	memcpy(pmic->descs, bd71837_regulators, sizeof(pmic->descs));

	pmic->pdev = pdev;
	pmic->mfd = dev_get_drvdata(pdev->dev.parent);

	if (!pmic->mfd) {
		dev_err(&pdev->dev, "No MFD driver data\n");
		err = -EINVAL;
		goto err;
	}
	platform_set_drvdata(pdev, pmic);

	/* Register LOCK release */
	err = regmap_update_bits(pmic->mfd->regmap, BD71837_REG_REGLOCK,
				 (REGLOCK_PWRSEQ | REGLOCK_VREG), 0);
	if (err) {
		dev_err(&pmic->pdev->dev, "Failed to unlock PMIC (%d)\n", err);
		goto err;
	} else {
		dev_dbg(&pmic->pdev->dev, "Unlocked lock register 0x%x\n",
			BD71837_REG_REGLOCK);
	}

	/*
	 * There is a HW quirk in BD71837. The shutdown sequence timings for
	 * bucks/LDOs which are controlled via register interface are changed.
	 * At PMIC poweroff the voltage for BUCK6/7 is cut immediately at the
	 * beginning of shut-down sequence. As bucks 6 and 7 are parent
	 * supplies for LDO5 and LDO6 - this causes LDO5/6 voltage
	 * monitoring to errorneously detect under voltage and force PMIC to
	 * emergency state instead of poweroff. In order to avoid this we
	 * disable voltage monitoring for LDO5 and LDO6
	 */
	err = regmap_update_bits(pmic->mfd->regmap, BD718XX_REG_MVRFLTMASK2,
				 BD718XX_LDO5_VRMON80 | BD718XX_LDO6_VRMON80,
				 BD718XX_LDO5_VRMON80 | BD718XX_LDO6_VRMON80);
	if (err) {
		dev_err(&pmic->pdev->dev,
			"Failed to disable voltage monitoring\n");
		goto err;
	}

	for (i = 0; i < ARRAY_SIZE(pmic_regulator_inits); i++) {

		struct regulator_desc *desc;
		struct regulator_dev *rdev;

		desc = &pmic->descs[i];

		config.dev = pdev->dev.parent;
		config.driver_data = pmic;
		config.regmap = pmic->mfd->regmap;

		rdev = devm_regulator_register(&pdev->dev, desc, &config);
		if (IS_ERR(rdev)) {
			dev_err(pmic->mfd->dev,
				"failed to register %s regulator\n",
				desc->name);
			err = PTR_ERR(rdev);
			goto err;
		}
		/* Regulator register gets the regulator constraints and
		 * applies them (set_machine_constraints). This should have
		 * turned the control register(s) to correct values and we
		 * can now switch the control from PMIC state machine to the
		 * register interface
		 */
		err = regmap_update_bits(pmic->mfd->regmap,
					 pmic_regulator_inits[i].reg,
					 pmic_regulator_inits[i].mask,
					 0xFFFFFFFF);
		if (err) {
			dev_err(&pmic->pdev->dev,
				"Failed to write BUCK/LDO SEL bit for (%s)\n",
				desc->name);
			goto err;
		}

		pmic->rdev[i] = rdev;
	}

err:
	return err;
}