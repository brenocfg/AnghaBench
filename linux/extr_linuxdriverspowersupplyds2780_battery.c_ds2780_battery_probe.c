#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct power_supply_config {struct ds2780_device_info* drv_data; } ;
struct TYPE_13__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_4__ dev; } ;
struct TYPE_14__ {int /*<<< orphan*/  get_property; int /*<<< orphan*/  num_properties; int /*<<< orphan*/  properties; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct ds2780_device_info {TYPE_2__* bat; TYPE_4__* dev; TYPE_5__ bat_desc; int /*<<< orphan*/  w1_dev; } ;
struct TYPE_11__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_12__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  POWER_SUPPLY_TYPE_BATTERY ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_4__*) ; 
 struct ds2780_device_info* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds2780_attr_group ; 
 int /*<<< orphan*/  ds2780_battery_get_property ; 
 int /*<<< orphan*/  ds2780_battery_props ; 
 int /*<<< orphan*/  ds2780_param_eeprom_bin_attr ; 
 int /*<<< orphan*/  ds2780_user_eeprom_bin_attr ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct ds2780_device_info*) ; 
 TYPE_2__* power_supply_register (TYPE_4__*,TYPE_5__*,struct power_supply_config*) ; 
 int /*<<< orphan*/  power_supply_unregister (TYPE_2__*) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ds2780_battery_probe(struct platform_device *pdev)
{
	struct power_supply_config psy_cfg = {};
	int ret = 0;
	struct ds2780_device_info *dev_info;

	dev_info = devm_kzalloc(&pdev->dev, sizeof(*dev_info), GFP_KERNEL);
	if (!dev_info) {
		ret = -ENOMEM;
		goto fail;
	}

	platform_set_drvdata(pdev, dev_info);

	dev_info->dev			= &pdev->dev;
	dev_info->w1_dev		= pdev->dev.parent;
	dev_info->bat_desc.name		= dev_name(&pdev->dev);
	dev_info->bat_desc.type		= POWER_SUPPLY_TYPE_BATTERY;
	dev_info->bat_desc.properties	= ds2780_battery_props;
	dev_info->bat_desc.num_properties = ARRAY_SIZE(ds2780_battery_props);
	dev_info->bat_desc.get_property	= ds2780_battery_get_property;

	psy_cfg.drv_data		= dev_info;

	dev_info->bat = power_supply_register(&pdev->dev, &dev_info->bat_desc,
					      &psy_cfg);
	if (IS_ERR(dev_info->bat)) {
		dev_err(dev_info->dev, "failed to register battery\n");
		ret = PTR_ERR(dev_info->bat);
		goto fail;
	}

	ret = sysfs_create_group(&dev_info->bat->dev.kobj, &ds2780_attr_group);
	if (ret) {
		dev_err(dev_info->dev, "failed to create sysfs group\n");
		goto fail_unregister;
	}

	ret = sysfs_create_bin_file(&dev_info->bat->dev.kobj,
					&ds2780_param_eeprom_bin_attr);
	if (ret) {
		dev_err(dev_info->dev,
				"failed to create param eeprom bin file");
		goto fail_remove_group;
	}

	ret = sysfs_create_bin_file(&dev_info->bat->dev.kobj,
					&ds2780_user_eeprom_bin_attr);
	if (ret) {
		dev_err(dev_info->dev,
				"failed to create user eeprom bin file");
		goto fail_remove_bin_file;
	}

	return 0;

fail_remove_bin_file:
	sysfs_remove_bin_file(&dev_info->bat->dev.kobj,
				&ds2780_param_eeprom_bin_attr);
fail_remove_group:
	sysfs_remove_group(&dev_info->bat->dev.kobj, &ds2780_attr_group);
fail_unregister:
	power_supply_unregister(dev_info->bat);
fail:
	return ret;
}