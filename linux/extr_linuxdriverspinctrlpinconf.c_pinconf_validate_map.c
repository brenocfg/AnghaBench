#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  configs; int /*<<< orphan*/  num_configs; int /*<<< orphan*/  group_or_pin; } ;
struct TYPE_4__ {TYPE_1__ configs; } ;
struct pinctrl_map {int /*<<< orphan*/  name; TYPE_2__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

int pinconf_validate_map(const struct pinctrl_map *map, int i)
{
	if (!map->data.configs.group_or_pin) {
		pr_err("failed to register map %s (%d): no group/pin given\n",
		       map->name, i);
		return -EINVAL;
	}

	if (!map->data.configs.num_configs ||
			!map->data.configs.configs) {
		pr_err("failed to register map %s (%d): no configs given\n",
		       map->name, i);
		return -EINVAL;
	}

	return 0;
}