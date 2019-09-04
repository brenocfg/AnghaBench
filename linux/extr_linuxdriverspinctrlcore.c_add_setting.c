#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pinctrl_state {int /*<<< orphan*/  settings; } ;
struct pinctrl_setting {int type; int /*<<< orphan*/  node; int /*<<< orphan*/  dev_name; struct pinctrl_dev* pctldev; } ;
struct pinctrl_map {int type; int /*<<< orphan*/  dev_name; int /*<<< orphan*/  ctrl_dev_name; int /*<<< orphan*/  name; } ;
struct pinctrl_dev {int dummy; } ;
struct pinctrl {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct pinctrl_state*) ; 
#define  PIN_MAP_TYPE_CONFIGS_GROUP 130 
#define  PIN_MAP_TYPE_CONFIGS_PIN 129 
 int PIN_MAP_TYPE_DUMMY_STATE ; 
#define  PIN_MAP_TYPE_MUX_GROUP 128 
 int PTR_ERR (struct pinctrl_state*) ; 
 struct pinctrl_state* create_state (struct pinctrl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct pinctrl_state* find_state (struct pinctrl*,int /*<<< orphan*/ ) ; 
 struct pinctrl_dev* get_pinctrl_dev_from_devname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pinctrl_setting*) ; 
 struct pinctrl_setting* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pinconf_map_to_setting (struct pinctrl_map const*,struct pinctrl_setting*) ; 
 int pinmux_map_to_setting (struct pinctrl_map const*,struct pinctrl_setting*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_setting(struct pinctrl *p, struct pinctrl_dev *pctldev,
		       const struct pinctrl_map *map)
{
	struct pinctrl_state *state;
	struct pinctrl_setting *setting;
	int ret;

	state = find_state(p, map->name);
	if (!state)
		state = create_state(p, map->name);
	if (IS_ERR(state))
		return PTR_ERR(state);

	if (map->type == PIN_MAP_TYPE_DUMMY_STATE)
		return 0;

	setting = kzalloc(sizeof(*setting), GFP_KERNEL);
	if (!setting)
		return -ENOMEM;

	setting->type = map->type;

	if (pctldev)
		setting->pctldev = pctldev;
	else
		setting->pctldev =
			get_pinctrl_dev_from_devname(map->ctrl_dev_name);
	if (!setting->pctldev) {
		kfree(setting);
		/* Do not defer probing of hogs (circular loop) */
		if (!strcmp(map->ctrl_dev_name, map->dev_name))
			return -ENODEV;
		/*
		 * OK let us guess that the driver is not there yet, and
		 * let's defer obtaining this pinctrl handle to later...
		 */
		dev_info(p->dev, "unknown pinctrl device %s in map entry, deferring probe",
			map->ctrl_dev_name);
		return -EPROBE_DEFER;
	}

	setting->dev_name = map->dev_name;

	switch (map->type) {
	case PIN_MAP_TYPE_MUX_GROUP:
		ret = pinmux_map_to_setting(map, setting);
		break;
	case PIN_MAP_TYPE_CONFIGS_PIN:
	case PIN_MAP_TYPE_CONFIGS_GROUP:
		ret = pinconf_map_to_setting(map, setting);
		break;
	default:
		ret = -EINVAL;
		break;
	}
	if (ret < 0) {
		kfree(setting);
		return ret;
	}

	list_add_tail(&setting->node, &state->settings);

	return 0;
}