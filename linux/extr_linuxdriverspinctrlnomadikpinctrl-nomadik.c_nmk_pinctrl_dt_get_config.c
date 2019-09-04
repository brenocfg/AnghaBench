#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device_node {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  property; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* nmk_cfg_params ; 
 scalar_t__ nmk_dt_pin_config (int,int,unsigned long*) ; 
 int of_property_read_u32 (struct device_node*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool nmk_pinctrl_dt_get_config(struct device_node *np,
		unsigned long *configs)
{
	bool has_config = 0;
	unsigned long cfg = 0;
	int i, val, ret;

	for (i = 0; i < ARRAY_SIZE(nmk_cfg_params); i++) {
		ret = of_property_read_u32(np,
				nmk_cfg_params[i].property, &val);
		if (ret != -EINVAL) {
			if (nmk_dt_pin_config(i, val, &cfg) == 0) {
				*configs |= cfg;
				has_config = 1;
			}
		}
	}

	return has_config;
}