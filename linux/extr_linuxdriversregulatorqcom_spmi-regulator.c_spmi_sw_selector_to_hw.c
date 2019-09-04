#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
struct spmi_voltage_range {unsigned int n_voltages; unsigned int set_point_min_uV; unsigned int min_uV; unsigned int step_uV; unsigned int range_sel; } ;
struct spmi_regulator {TYPE_1__* set_points; } ;
struct TYPE_2__ {int count; struct spmi_voltage_range* range; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int spmi_sw_selector_to_hw(struct spmi_regulator *vreg,
				  unsigned selector, u8 *range_sel,
				  u8 *voltage_sel)
{
	const struct spmi_voltage_range *range, *end;
	unsigned offset;

	range = vreg->set_points->range;
	end = range + vreg->set_points->count;

	for (; range < end; range++) {
		if (selector < range->n_voltages) {
			/*
			 * hardware selectors between set point min and real
			 * min are invalid so we ignore them
			 */
			offset = range->set_point_min_uV - range->min_uV;
			offset /= range->step_uV;
			*voltage_sel = selector + offset;
			*range_sel = range->range_sel;
			return 0;
		}

		selector -= range->n_voltages;
	}

	return -EINVAL;
}