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
typedef  size_t u32 ;
struct stm32_pinctrl_group {int /*<<< orphan*/  name; } ;
struct stm32_pinctrl {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  function; int /*<<< orphan*/  group; } ;
struct TYPE_4__ {TYPE_1__ mux; } ;
struct pinctrl_map {TYPE_2__ data; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  PIN_MAP_TYPE_MUX_GROUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 int /*<<< orphan*/ * stm32_gpio_functions ; 
 int /*<<< orphan*/  stm32_pctrl_is_function_valid (struct stm32_pinctrl*,size_t,size_t) ; 

__attribute__((used)) static int stm32_pctrl_dt_node_to_map_func(struct stm32_pinctrl *pctl,
		u32 pin, u32 fnum, struct stm32_pinctrl_group *grp,
		struct pinctrl_map **map, unsigned *reserved_maps,
		unsigned *num_maps)
{
	if (*num_maps == *reserved_maps)
		return -ENOSPC;

	(*map)[*num_maps].type = PIN_MAP_TYPE_MUX_GROUP;
	(*map)[*num_maps].data.mux.group = grp->name;

	if (!stm32_pctrl_is_function_valid(pctl, pin, fnum)) {
		dev_err(pctl->dev, "invalid function %d on pin %d .\n",
				fnum, pin);
		return -EINVAL;
	}

	(*map)[*num_maps].data.mux.function = stm32_gpio_functions[fnum];
	(*num_maps)++;

	return 0;
}