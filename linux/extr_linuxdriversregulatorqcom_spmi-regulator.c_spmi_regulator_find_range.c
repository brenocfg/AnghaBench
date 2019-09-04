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
typedef  scalar_t__ u8 ;
struct spmi_voltage_range {scalar_t__ range_sel; } ;
struct spmi_regulator {TYPE_1__* set_points; } ;
struct TYPE_2__ {int count; struct spmi_voltage_range* range; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPMI_COMMON_REG_VOLTAGE_RANGE ; 
 int /*<<< orphan*/  spmi_vreg_read (struct spmi_regulator*,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static const struct spmi_voltage_range *
spmi_regulator_find_range(struct spmi_regulator *vreg)
{
	u8 range_sel;
	const struct spmi_voltage_range *range, *end;

	range = vreg->set_points->range;
	end = range + vreg->set_points->count;

	spmi_vreg_read(vreg, SPMI_COMMON_REG_VOLTAGE_RANGE, &range_sel, 1);

	for (; range < end; range++)
		if (range->range_sel == range_sel)
			return range;

	return NULL;
}