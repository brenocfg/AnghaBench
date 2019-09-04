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
typedef  int u8 ;
struct spmi_voltage_range {int step_uV; } ;
struct spmi_regulator {int logical_type; int /*<<< orphan*/  slew_rate; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPMI_COMMON_REG_STEP_CTRL ; 
 int SPMI_DEFAULT_STEP_DELAY ; 
 int SPMI_FTSMPS_CLOCK_RATE ; 
 int SPMI_FTSMPS_STEP_CTRL_DELAY_MASK ; 
 int SPMI_FTSMPS_STEP_CTRL_DELAY_SHIFT ; 
 int SPMI_FTSMPS_STEP_CTRL_STEP_MASK ; 
 int SPMI_FTSMPS_STEP_CTRL_STEP_SHIFT ; 
 int SPMI_FTSMPS_STEP_DELAY ; 
 int SPMI_FTSMPS_STEP_MARGIN_DEN ; 
 int SPMI_FTSMPS_STEP_MARGIN_NUM ; 
#define  SPMI_REGULATOR_LOGICAL_TYPE_FTSMPS 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  max (int,int) ; 
 struct spmi_voltage_range* spmi_regulator_find_range (struct spmi_regulator*) ; 
 int spmi_vreg_read (struct spmi_regulator*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int spmi_regulator_init_slew_rate(struct spmi_regulator *vreg)
{
	int ret;
	u8 reg = 0;
	int step, delay, slew_rate, step_delay;
	const struct spmi_voltage_range *range;

	ret = spmi_vreg_read(vreg, SPMI_COMMON_REG_STEP_CTRL, &reg, 1);
	if (ret) {
		dev_err(vreg->dev, "spmi read failed, ret=%d\n", ret);
		return ret;
	}

	range = spmi_regulator_find_range(vreg);
	if (!range)
		return -EINVAL;

	switch (vreg->logical_type) {
	case SPMI_REGULATOR_LOGICAL_TYPE_FTSMPS:
		step_delay = SPMI_FTSMPS_STEP_DELAY;
		break;
	default:
		step_delay = SPMI_DEFAULT_STEP_DELAY;
		break;
	}

	step = reg & SPMI_FTSMPS_STEP_CTRL_STEP_MASK;
	step >>= SPMI_FTSMPS_STEP_CTRL_STEP_SHIFT;

	delay = reg & SPMI_FTSMPS_STEP_CTRL_DELAY_MASK;
	delay >>= SPMI_FTSMPS_STEP_CTRL_DELAY_SHIFT;

	/* slew_rate has units of uV/us */
	slew_rate = SPMI_FTSMPS_CLOCK_RATE * range->step_uV * (1 << step);
	slew_rate /= 1000 * (step_delay << delay);
	slew_rate *= SPMI_FTSMPS_STEP_MARGIN_NUM;
	slew_rate /= SPMI_FTSMPS_STEP_MARGIN_DEN;

	/* Ensure that the slew rate is greater than 0 */
	vreg->slew_rate = max(slew_rate, 1);

	return ret;
}