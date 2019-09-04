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
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int id; char* name; char* supply_name; char* of_match; int /*<<< orphan*/  type; int /*<<< orphan*/  owner; int /*<<< orphan*/ * ops; } ;
struct smbb_charger {int revision; scalar_t__ addr; int /*<<< orphan*/  regmap; void* jeita_ext_temp; void* otg_reg; TYPE_3__ otg_rdesc; void* dc_psy; void* dc_disabled; void* edev; void* usb_psy; void* bat_psy; int /*<<< orphan*/  statlock; TYPE_1__* dev; } ;
struct regulator_config {struct smbb_charger* driver_data; TYPE_1__* dev; } ;
struct reg_off_mask_default {int rev_mask; int mask; int value; scalar_t__ offset; int /*<<< orphan*/  name; int /*<<< orphan*/  (* handler ) (int,struct smbb_charger*) ;} ;
struct power_supply_config {int num_supplicants; struct reg_off_mask_default* supplied_to; struct smbb_charger* drv_data; int /*<<< orphan*/  of_node; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct reg_off_mask_default*) ; 
 int BIT (int) ; 
 int BTC_CTRL_COLD_EXT ; 
 int BTC_CTRL_HOT_EXT_N ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 scalar_t__ SMBB_BAT_BTC_CTRL ; 
 scalar_t__ SMBB_MISC_REV2 ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int _ATTR_CNT ; 
 int /*<<< orphan*/  bat_psy_desc ; 
 int /*<<< orphan*/  dc_psy_desc ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int) ; 
 void* devm_extcon_dev_allocate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int devm_extcon_dev_register (TYPE_1__*,void*) ; 
 struct smbb_charger* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 void* devm_power_supply_register (TYPE_1__*,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 void* devm_regulator_register (TYPE_1__*,TYPE_3__*,struct regulator_config*) ; 
 int devm_request_threaded_irq (TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int,struct smbb_charger*),int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct smbb_charger*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 void* of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int platform_get_irq_byname (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct smbb_charger*) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int,int) ; 
 struct reg_off_mask_default* smbb_bif ; 
 int smbb_charger_attr_parse (struct smbb_charger*,int) ; 
 struct reg_off_mask_default* smbb_charger_irqs ; 
 struct reg_off_mask_default* smbb_charger_setup ; 
 int /*<<< orphan*/  smbb_chg_otg_ops ; 
 int /*<<< orphan*/  smbb_usb_extcon_cable ; 
 int /*<<< orphan*/  stub1 (int,struct smbb_charger*) ; 
 int /*<<< orphan*/  usb_psy_desc ; 

__attribute__((used)) static int smbb_charger_probe(struct platform_device *pdev)
{
	struct power_supply_config bat_cfg = {};
	struct power_supply_config usb_cfg = {};
	struct power_supply_config dc_cfg = {};
	struct smbb_charger *chg;
	struct regulator_config config = { };
	int rc, i;

	chg = devm_kzalloc(&pdev->dev, sizeof(*chg), GFP_KERNEL);
	if (!chg)
		return -ENOMEM;

	chg->dev = &pdev->dev;
	mutex_init(&chg->statlock);

	chg->regmap = dev_get_regmap(pdev->dev.parent, NULL);
	if (!chg->regmap) {
		dev_err(&pdev->dev, "failed to locate regmap\n");
		return -ENODEV;
	}

	rc = of_property_read_u32(pdev->dev.of_node, "reg", &chg->addr);
	if (rc) {
		dev_err(&pdev->dev, "missing or invalid 'reg' property\n");
		return rc;
	}

	rc = regmap_read(chg->regmap, chg->addr + SMBB_MISC_REV2, &chg->revision);
	if (rc) {
		dev_err(&pdev->dev, "unable to read revision\n");
		return rc;
	}

	chg->revision += 1;
	if (chg->revision != 2 && chg->revision != 3) {
		dev_err(&pdev->dev, "v1 hardware not supported\n");
		return -ENODEV;
	}
	dev_info(&pdev->dev, "Initializing SMBB rev %u", chg->revision);

	chg->dc_disabled = of_property_read_bool(pdev->dev.of_node, "qcom,disable-dc");

	for (i = 0; i < _ATTR_CNT; ++i) {
		rc = smbb_charger_attr_parse(chg, i);
		if (rc) {
			dev_err(&pdev->dev, "failed to parse/apply settings\n");
			return rc;
		}
	}

	bat_cfg.drv_data = chg;
	bat_cfg.of_node = pdev->dev.of_node;
	chg->bat_psy = devm_power_supply_register(&pdev->dev,
						  &bat_psy_desc,
						  &bat_cfg);
	if (IS_ERR(chg->bat_psy)) {
		dev_err(&pdev->dev, "failed to register battery\n");
		return PTR_ERR(chg->bat_psy);
	}

	usb_cfg.drv_data = chg;
	usb_cfg.supplied_to = smbb_bif;
	usb_cfg.num_supplicants = ARRAY_SIZE(smbb_bif);
	chg->usb_psy = devm_power_supply_register(&pdev->dev,
						  &usb_psy_desc,
						  &usb_cfg);
	if (IS_ERR(chg->usb_psy)) {
		dev_err(&pdev->dev, "failed to register USB power supply\n");
		return PTR_ERR(chg->usb_psy);
	}

	chg->edev = devm_extcon_dev_allocate(&pdev->dev, smbb_usb_extcon_cable);
	if (IS_ERR(chg->edev)) {
		dev_err(&pdev->dev, "failed to allocate extcon device\n");
		return -ENOMEM;
	}

	rc = devm_extcon_dev_register(&pdev->dev, chg->edev);
	if (rc < 0) {
		dev_err(&pdev->dev, "failed to register extcon device\n");
		return rc;
	}

	if (!chg->dc_disabled) {
		dc_cfg.drv_data = chg;
		dc_cfg.supplied_to = smbb_bif;
		dc_cfg.num_supplicants = ARRAY_SIZE(smbb_bif);
		chg->dc_psy = devm_power_supply_register(&pdev->dev,
							 &dc_psy_desc,
							 &dc_cfg);
		if (IS_ERR(chg->dc_psy)) {
			dev_err(&pdev->dev, "failed to register DC power supply\n");
			return PTR_ERR(chg->dc_psy);
		}
	}

	for (i = 0; i < ARRAY_SIZE(smbb_charger_irqs); ++i) {
		int irq;

		irq = platform_get_irq_byname(pdev, smbb_charger_irqs[i].name);
		if (irq < 0) {
			dev_err(&pdev->dev, "failed to get irq '%s'\n",
				smbb_charger_irqs[i].name);
			return irq;
		}

		smbb_charger_irqs[i].handler(irq, chg);

		rc = devm_request_threaded_irq(&pdev->dev, irq, NULL,
				smbb_charger_irqs[i].handler, IRQF_ONESHOT,
				smbb_charger_irqs[i].name, chg);
		if (rc) {
			dev_err(&pdev->dev, "failed to request irq '%s'\n",
				smbb_charger_irqs[i].name);
			return rc;
		}
	}

	/*
	 * otg regulator is used to control VBUS voltage direction
	 * when USB switches between host and gadget mode
	 */
	chg->otg_rdesc.id = -1;
	chg->otg_rdesc.name = "otg-vbus";
	chg->otg_rdesc.ops = &smbb_chg_otg_ops;
	chg->otg_rdesc.owner = THIS_MODULE;
	chg->otg_rdesc.type = REGULATOR_VOLTAGE;
	chg->otg_rdesc.supply_name = "usb-otg-in";
	chg->otg_rdesc.of_match = "otg-vbus";

	config.dev = &pdev->dev;
	config.driver_data = chg;

	chg->otg_reg = devm_regulator_register(&pdev->dev, &chg->otg_rdesc,
					       &config);
	if (IS_ERR(chg->otg_reg))
		return PTR_ERR(chg->otg_reg);

	chg->jeita_ext_temp = of_property_read_bool(pdev->dev.of_node,
			"qcom,jeita-extended-temp-range");

	/* Set temperature range to [35%:70%] or [25%:80%] accordingly */
	rc = regmap_update_bits(chg->regmap, chg->addr + SMBB_BAT_BTC_CTRL,
			BTC_CTRL_COLD_EXT | BTC_CTRL_HOT_EXT_N,
			chg->jeita_ext_temp ?
				BTC_CTRL_COLD_EXT :
				BTC_CTRL_HOT_EXT_N);
	if (rc) {
		dev_err(&pdev->dev,
			"unable to set %s temperature range\n",
			chg->jeita_ext_temp ? "JEITA extended" : "normal");
		return rc;
	}

	for (i = 0; i < ARRAY_SIZE(smbb_charger_setup); ++i) {
		const struct reg_off_mask_default *r = &smbb_charger_setup[i];

		if (r->rev_mask & BIT(chg->revision))
			continue;

		rc = regmap_update_bits(chg->regmap, chg->addr + r->offset,
				r->mask, r->value);
		if (rc) {
			dev_err(&pdev->dev,
				"unable to initializing charging, bailing\n");
			return rc;
		}
	}

	platform_set_drvdata(pdev, chg);

	return 0;
}