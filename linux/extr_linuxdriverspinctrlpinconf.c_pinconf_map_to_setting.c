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
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int group_or_pin; int /*<<< orphan*/  configs; int /*<<< orphan*/  num_configs; } ;
struct TYPE_6__ {TYPE_1__ configs; } ;
struct pinctrl_setting {int type; TYPE_2__ data; struct pinctrl_dev* pctldev; } ;
struct TYPE_7__ {int /*<<< orphan*/  configs; int /*<<< orphan*/  num_configs; int /*<<< orphan*/  group_or_pin; } ;
struct TYPE_8__ {TYPE_3__ configs; } ;
struct pinctrl_map {TYPE_4__ data; } ;
struct pinctrl_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PIN_MAP_TYPE_CONFIGS_GROUP 129 
#define  PIN_MAP_TYPE_CONFIGS_PIN 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int pin_get_from_name (struct pinctrl_dev*,int /*<<< orphan*/ ) ; 
 int pinctrl_get_group_selector (struct pinctrl_dev*,int /*<<< orphan*/ ) ; 

int pinconf_map_to_setting(const struct pinctrl_map *map,
			  struct pinctrl_setting *setting)
{
	struct pinctrl_dev *pctldev = setting->pctldev;
	int pin;

	switch (setting->type) {
	case PIN_MAP_TYPE_CONFIGS_PIN:
		pin = pin_get_from_name(pctldev,
					map->data.configs.group_or_pin);
		if (pin < 0) {
			dev_err(pctldev->dev, "could not map pin config for \"%s\"",
				map->data.configs.group_or_pin);
			return pin;
		}
		setting->data.configs.group_or_pin = pin;
		break;
	case PIN_MAP_TYPE_CONFIGS_GROUP:
		pin = pinctrl_get_group_selector(pctldev,
					 map->data.configs.group_or_pin);
		if (pin < 0) {
			dev_err(pctldev->dev, "could not map group config for \"%s\"",
				map->data.configs.group_or_pin);
			return pin;
		}
		setting->data.configs.group_or_pin = pin;
		break;
	default:
		return -EINVAL;
	}

	setting->data.configs.num_configs = map->data.configs.num_configs;
	setting->data.configs.configs = map->data.configs.configs;

	return 0;
}