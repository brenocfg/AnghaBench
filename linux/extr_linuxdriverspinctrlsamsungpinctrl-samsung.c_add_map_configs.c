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
struct TYPE_3__ {char const* group_or_pin; unsigned long* configs; unsigned int num_configs; } ;
struct TYPE_4__ {TYPE_1__ configs; } ;
struct pinctrl_map {TYPE_2__ data; int /*<<< orphan*/  type; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PIN_MAP_TYPE_CONFIGS_GROUP ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned long* kmemdup (unsigned long*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_map_configs(struct device *dev, struct pinctrl_map **map,
			   unsigned *reserved_maps, unsigned *num_maps,
			   const char *group, unsigned long *configs,
			   unsigned num_configs)
{
	unsigned long *dup_configs;

	if (WARN_ON(*num_maps == *reserved_maps))
		return -ENOSPC;

	dup_configs = kmemdup(configs, num_configs * sizeof(*dup_configs),
			      GFP_KERNEL);
	if (!dup_configs)
		return -ENOMEM;

	(*map)[*num_maps].type = PIN_MAP_TYPE_CONFIGS_GROUP;
	(*map)[*num_maps].data.configs.group_or_pin = group;
	(*map)[*num_maps].data.configs.configs = dup_configs;
	(*map)[*num_maps].data.configs.num_configs = num_configs;
	(*num_maps)++;

	return 0;
}