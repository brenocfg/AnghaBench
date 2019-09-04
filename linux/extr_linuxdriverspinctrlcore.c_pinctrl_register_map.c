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
struct pinctrl_maps {unsigned int num_maps; int /*<<< orphan*/  node; struct pinctrl_map const* maps; } ;
struct pinctrl_map {int type; int /*<<< orphan*/  name; int /*<<< orphan*/  ctrl_dev_name; int /*<<< orphan*/  dev_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  PIN_MAP_TYPE_CONFIGS_GROUP 131 
#define  PIN_MAP_TYPE_CONFIGS_PIN 130 
#define  PIN_MAP_TYPE_DUMMY_STATE 129 
#define  PIN_MAP_TYPE_MUX_GROUP 128 
 int /*<<< orphan*/  kfree (struct pinctrl_maps*) ; 
 struct pinctrl_map const* kmemdup (struct pinctrl_map const*,int,int /*<<< orphan*/ ) ; 
 struct pinctrl_maps* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int pinconf_validate_map (struct pinctrl_map const*,int) ; 
 int /*<<< orphan*/  pinctrl_maps ; 
 int /*<<< orphan*/  pinctrl_maps_mutex ; 
 int pinmux_validate_map (struct pinctrl_map const*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 

int pinctrl_register_map(const struct pinctrl_map *maps, unsigned num_maps,
			 bool dup)
{
	int i, ret;
	struct pinctrl_maps *maps_node;

	pr_debug("add %u pinctrl maps\n", num_maps);

	/* First sanity check the new mapping */
	for (i = 0; i < num_maps; i++) {
		if (!maps[i].dev_name) {
			pr_err("failed to register map %s (%d): no device given\n",
			       maps[i].name, i);
			return -EINVAL;
		}

		if (!maps[i].name) {
			pr_err("failed to register map %d: no map name given\n",
			       i);
			return -EINVAL;
		}

		if (maps[i].type != PIN_MAP_TYPE_DUMMY_STATE &&
				!maps[i].ctrl_dev_name) {
			pr_err("failed to register map %s (%d): no pin control device given\n",
			       maps[i].name, i);
			return -EINVAL;
		}

		switch (maps[i].type) {
		case PIN_MAP_TYPE_DUMMY_STATE:
			break;
		case PIN_MAP_TYPE_MUX_GROUP:
			ret = pinmux_validate_map(&maps[i], i);
			if (ret < 0)
				return ret;
			break;
		case PIN_MAP_TYPE_CONFIGS_PIN:
		case PIN_MAP_TYPE_CONFIGS_GROUP:
			ret = pinconf_validate_map(&maps[i], i);
			if (ret < 0)
				return ret;
			break;
		default:
			pr_err("failed to register map %s (%d): invalid type given\n",
			       maps[i].name, i);
			return -EINVAL;
		}
	}

	maps_node = kzalloc(sizeof(*maps_node), GFP_KERNEL);
	if (!maps_node)
		return -ENOMEM;

	maps_node->num_maps = num_maps;
	if (dup) {
		maps_node->maps = kmemdup(maps, sizeof(*maps) * num_maps,
					  GFP_KERNEL);
		if (!maps_node->maps) {
			kfree(maps_node);
			return -ENOMEM;
		}
	} else {
		maps_node->maps = maps;
	}

	mutex_lock(&pinctrl_maps_mutex);
	list_add_tail(&maps_node->node, &pinctrl_maps);
	mutex_unlock(&pinctrl_maps_mutex);

	return 0;
}