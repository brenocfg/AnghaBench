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
typedef  int u32 ;
struct regulator_state {unsigned int mode; int min_uV; int max_uV; int uV; int changeable; int /*<<< orphan*/  enabled; } ;
struct regulation_constraints {int min_uV; int max_uV; int apply_uV; int uV_offset; int min_uA; int max_uA; int ilim_uA; int ramp_delay; int ramp_disable; int settling_time; int settling_time_up; int settling_time_down; int enable_time; unsigned int initial_mode; unsigned int valid_modes_mask; int system_load; int max_spread; int initial_state; struct regulator_state state_disk; struct regulator_state state_mem; void* over_current_protection; int /*<<< orphan*/  valid_ops_mask; int /*<<< orphan*/  active_discharge; void* soft_start; void* pull_down; void* always_on; void* boot_on; int /*<<< orphan*/  name; } ;
struct regulator_init_data {struct regulation_constraints constraints; } ;
struct regulator_desc {unsigned int (* of_map_mode ) (int) ;} ;
struct device_node {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DISABLE_IN_SUSPEND ; 
 int /*<<< orphan*/  ENABLE_IN_SUSPEND ; 
#define  PM_SUSPEND_MAX 132 
#define  PM_SUSPEND_MEM 131 
#define  PM_SUSPEND_ON 130 
#define  PM_SUSPEND_STANDBY 129 
#define  PM_SUSPEND_TO_IDLE 128 
 int /*<<< orphan*/  REGULATOR_ACTIVE_DISCHARGE_DISABLE ; 
 int /*<<< orphan*/  REGULATOR_ACTIVE_DISCHARGE_ENABLE ; 
 int /*<<< orphan*/  REGULATOR_CHANGE_BYPASS ; 
 int /*<<< orphan*/  REGULATOR_CHANGE_CURRENT ; 
 int /*<<< orphan*/  REGULATOR_CHANGE_DRMS ; 
 int /*<<< orphan*/  REGULATOR_CHANGE_MODE ; 
 int /*<<< orphan*/  REGULATOR_CHANGE_STATUS ; 
 int /*<<< orphan*/  REGULATOR_CHANGE_VOLTAGE ; 
 unsigned int REGULATOR_MODE_INVALID ; 
 struct device_node* of_get_child_by_name (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_count_elems_of_size (struct device_node*,char*,int) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int of_property_read_u32_index (struct device_node*,char*,int,int*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * regulator_states ; 
 unsigned int stub1 (int) ; 
 unsigned int stub2 (int) ; 
 unsigned int stub3 (int) ; 

__attribute__((used)) static void of_get_regulation_constraints(struct device_node *np,
					struct regulator_init_data **init_data,
					const struct regulator_desc *desc)
{
	struct regulation_constraints *constraints = &(*init_data)->constraints;
	struct regulator_state *suspend_state;
	struct device_node *suspend_np;
	unsigned int mode;
	int ret, i, len;
	u32 pval;

	constraints->name = of_get_property(np, "regulator-name", NULL);

	if (!of_property_read_u32(np, "regulator-min-microvolt", &pval))
		constraints->min_uV = pval;

	if (!of_property_read_u32(np, "regulator-max-microvolt", &pval))
		constraints->max_uV = pval;

	/* Voltage change possible? */
	if (constraints->min_uV != constraints->max_uV)
		constraints->valid_ops_mask |= REGULATOR_CHANGE_VOLTAGE;

	/* Do we have a voltage range, if so try to apply it? */
	if (constraints->min_uV && constraints->max_uV)
		constraints->apply_uV = true;

	if (!of_property_read_u32(np, "regulator-microvolt-offset", &pval))
		constraints->uV_offset = pval;
	if (!of_property_read_u32(np, "regulator-min-microamp", &pval))
		constraints->min_uA = pval;
	if (!of_property_read_u32(np, "regulator-max-microamp", &pval))
		constraints->max_uA = pval;

	if (!of_property_read_u32(np, "regulator-input-current-limit-microamp",
				  &pval))
		constraints->ilim_uA = pval;

	/* Current change possible? */
	if (constraints->min_uA != constraints->max_uA)
		constraints->valid_ops_mask |= REGULATOR_CHANGE_CURRENT;

	constraints->boot_on = of_property_read_bool(np, "regulator-boot-on");
	constraints->always_on = of_property_read_bool(np, "regulator-always-on");
	if (!constraints->always_on) /* status change should be possible. */
		constraints->valid_ops_mask |= REGULATOR_CHANGE_STATUS;

	constraints->pull_down = of_property_read_bool(np, "regulator-pull-down");

	if (of_property_read_bool(np, "regulator-allow-bypass"))
		constraints->valid_ops_mask |= REGULATOR_CHANGE_BYPASS;

	if (of_property_read_bool(np, "regulator-allow-set-load"))
		constraints->valid_ops_mask |= REGULATOR_CHANGE_DRMS;

	ret = of_property_read_u32(np, "regulator-ramp-delay", &pval);
	if (!ret) {
		if (pval)
			constraints->ramp_delay = pval;
		else
			constraints->ramp_disable = true;
	}

	ret = of_property_read_u32(np, "regulator-settling-time-us", &pval);
	if (!ret)
		constraints->settling_time = pval;

	ret = of_property_read_u32(np, "regulator-settling-time-up-us", &pval);
	if (!ret)
		constraints->settling_time_up = pval;
	if (constraints->settling_time_up && constraints->settling_time) {
		pr_warn("%s: ambiguous configuration for settling time, ignoring 'regulator-settling-time-up-us'\n",
			np->name);
		constraints->settling_time_up = 0;
	}

	ret = of_property_read_u32(np, "regulator-settling-time-down-us",
				   &pval);
	if (!ret)
		constraints->settling_time_down = pval;
	if (constraints->settling_time_down && constraints->settling_time) {
		pr_warn("%s: ambiguous configuration for settling time, ignoring 'regulator-settling-time-down-us'\n",
			np->name);
		constraints->settling_time_down = 0;
	}

	ret = of_property_read_u32(np, "regulator-enable-ramp-delay", &pval);
	if (!ret)
		constraints->enable_time = pval;

	constraints->soft_start = of_property_read_bool(np,
					"regulator-soft-start");
	ret = of_property_read_u32(np, "regulator-active-discharge", &pval);
	if (!ret) {
		constraints->active_discharge =
				(pval) ? REGULATOR_ACTIVE_DISCHARGE_ENABLE :
					REGULATOR_ACTIVE_DISCHARGE_DISABLE;
	}

	if (!of_property_read_u32(np, "regulator-initial-mode", &pval)) {
		if (desc && desc->of_map_mode) {
			mode = desc->of_map_mode(pval);
			if (mode == REGULATOR_MODE_INVALID)
				pr_err("%s: invalid mode %u\n", np->name, pval);
			else
				constraints->initial_mode = mode;
		} else {
			pr_warn("%s: mapping for mode %d not defined\n",
				np->name, pval);
		}
	}

	len = of_property_count_elems_of_size(np, "regulator-allowed-modes",
						sizeof(u32));
	if (len > 0) {
		if (desc && desc->of_map_mode) {
			for (i = 0; i < len; i++) {
				ret = of_property_read_u32_index(np,
					"regulator-allowed-modes", i, &pval);
				if (ret) {
					pr_err("%s: couldn't read allowed modes index %d, ret=%d\n",
						np->name, i, ret);
					break;
				}
				mode = desc->of_map_mode(pval);
				if (mode == REGULATOR_MODE_INVALID)
					pr_err("%s: invalid regulator-allowed-modes element %u\n",
						np->name, pval);
				else
					constraints->valid_modes_mask |= mode;
			}
			if (constraints->valid_modes_mask)
				constraints->valid_ops_mask
					|= REGULATOR_CHANGE_MODE;
		} else {
			pr_warn("%s: mode mapping not defined\n", np->name);
		}
	}

	if (!of_property_read_u32(np, "regulator-system-load", &pval))
		constraints->system_load = pval;

	if (!of_property_read_u32(np, "regulator-coupled-max-spread",
				  &pval))
		constraints->max_spread = pval;

	constraints->over_current_protection = of_property_read_bool(np,
					"regulator-over-current-protection");

	for (i = 0; i < ARRAY_SIZE(regulator_states); i++) {
		switch (i) {
		case PM_SUSPEND_MEM:
			suspend_state = &constraints->state_mem;
			break;
		case PM_SUSPEND_MAX:
			suspend_state = &constraints->state_disk;
			break;
		case PM_SUSPEND_ON:
		case PM_SUSPEND_TO_IDLE:
		case PM_SUSPEND_STANDBY:
		default:
			continue;
		}

		suspend_np = of_get_child_by_name(np, regulator_states[i]);
		if (!suspend_np || !suspend_state)
			continue;

		if (!of_property_read_u32(suspend_np, "regulator-mode",
					  &pval)) {
			if (desc && desc->of_map_mode) {
				mode = desc->of_map_mode(pval);
				if (mode == REGULATOR_MODE_INVALID)
					pr_err("%s: invalid mode %u\n",
					       np->name, pval);
				else
					suspend_state->mode = mode;
			} else {
				pr_warn("%s: mapping for mode %d not defined\n",
					np->name, pval);
			}
		}

		if (of_property_read_bool(suspend_np,
					"regulator-on-in-suspend"))
			suspend_state->enabled = ENABLE_IN_SUSPEND;
		else if (of_property_read_bool(suspend_np,
					"regulator-off-in-suspend"))
			suspend_state->enabled = DISABLE_IN_SUSPEND;

		if (!of_property_read_u32(np, "regulator-suspend-min-microvolt",
					  &pval))
			suspend_state->min_uV = pval;

		if (!of_property_read_u32(np, "regulator-suspend-max-microvolt",
					  &pval))
			suspend_state->max_uV = pval;

		if (!of_property_read_u32(suspend_np,
					"regulator-suspend-microvolt", &pval))
			suspend_state->uV = pval;
		else /* otherwise use min_uV as default suspend voltage */
			suspend_state->uV = suspend_state->min_uV;

		if (of_property_read_bool(suspend_np,
					"regulator-changeable-in-suspend"))
			suspend_state->changeable = true;

		if (i == PM_SUSPEND_MEM)
			constraints->initial_state = PM_SUSPEND_MEM;

		of_node_put(suspend_np);
		suspend_state = NULL;
		suspend_np = NULL;
	}
}