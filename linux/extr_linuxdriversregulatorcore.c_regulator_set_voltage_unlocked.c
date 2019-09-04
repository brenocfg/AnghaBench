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
typedef  size_t suspend_state_t ;
struct regulator_voltage {int min_uV; int max_uV; } ;
struct regulator_dev {int /*<<< orphan*/  dev; struct regulator* supply; TYPE_2__* desc; } ;
struct regulator {struct regulator_dev* rdev; struct regulator_voltage* voltage; } ;
struct TYPE_4__ {scalar_t__ min_dropout_uV; TYPE_1__* ops; } ;
struct TYPE_3__ {scalar_t__ get_voltage_sel; scalar_t__ get_voltage; int /*<<< orphan*/  set_voltage_sel; int /*<<< orphan*/  set_voltage; } ;

/* Variables and functions */
 int EINVAL ; 
 int INT_MAX ; 
 size_t PM_SUSPEND_ON ; 
 int /*<<< orphan*/  REGULATOR_CHANGE_VOLTAGE ; 
 int _regulator_do_set_suspend_voltage (struct regulator_dev*,int,int,size_t) ; 
 int _regulator_do_set_voltage (struct regulator_dev*,int,int) ; 
 int _regulator_get_voltage (struct regulator_dev*) ; 
 int _regulator_list_voltage (struct regulator_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int regulator_check_consumers (struct regulator_dev*,int*,int*,size_t) ; 
 int regulator_check_voltage (struct regulator_dev*,int*,int*) ; 
 int regulator_map_voltage (struct regulator_dev*,int,int) ; 
 scalar_t__ regulator_ops_is_valid (struct regulator_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regulator_set_voltage_unlocked(struct regulator *regulator,
					  int min_uV, int max_uV,
					  suspend_state_t state)
{
	struct regulator_dev *rdev = regulator->rdev;
	struct regulator_voltage *voltage = &regulator->voltage[state];
	int ret = 0;
	int old_min_uV, old_max_uV;
	int current_uV;
	int best_supply_uV = 0;
	int supply_change_uV = 0;

	/* If we're setting the same range as last time the change
	 * should be a noop (some cpufreq implementations use the same
	 * voltage for multiple frequencies, for example).
	 */
	if (voltage->min_uV == min_uV && voltage->max_uV == max_uV)
		goto out;

	/* If we're trying to set a range that overlaps the current voltage,
	 * return successfully even though the regulator does not support
	 * changing the voltage.
	 */
	if (!regulator_ops_is_valid(rdev, REGULATOR_CHANGE_VOLTAGE)) {
		current_uV = _regulator_get_voltage(rdev);
		if (min_uV <= current_uV && current_uV <= max_uV) {
			voltage->min_uV = min_uV;
			voltage->max_uV = max_uV;
			goto out;
		}
	}

	/* sanity check */
	if (!rdev->desc->ops->set_voltage &&
	    !rdev->desc->ops->set_voltage_sel) {
		ret = -EINVAL;
		goto out;
	}

	/* constraints check */
	ret = regulator_check_voltage(rdev, &min_uV, &max_uV);
	if (ret < 0)
		goto out;

	/* restore original values in case of error */
	old_min_uV = voltage->min_uV;
	old_max_uV = voltage->max_uV;
	voltage->min_uV = min_uV;
	voltage->max_uV = max_uV;

	ret = regulator_check_consumers(rdev, &min_uV, &max_uV, state);
	if (ret < 0)
		goto out2;

	if (rdev->supply &&
	    regulator_ops_is_valid(rdev->supply->rdev,
				   REGULATOR_CHANGE_VOLTAGE) &&
	    (rdev->desc->min_dropout_uV || !(rdev->desc->ops->get_voltage ||
					   rdev->desc->ops->get_voltage_sel))) {
		int current_supply_uV;
		int selector;

		selector = regulator_map_voltage(rdev, min_uV, max_uV);
		if (selector < 0) {
			ret = selector;
			goto out2;
		}

		best_supply_uV = _regulator_list_voltage(rdev, selector, 0);
		if (best_supply_uV < 0) {
			ret = best_supply_uV;
			goto out2;
		}

		best_supply_uV += rdev->desc->min_dropout_uV;

		current_supply_uV = _regulator_get_voltage(rdev->supply->rdev);
		if (current_supply_uV < 0) {
			ret = current_supply_uV;
			goto out2;
		}

		supply_change_uV = best_supply_uV - current_supply_uV;
	}

	if (supply_change_uV > 0) {
		ret = regulator_set_voltage_unlocked(rdev->supply,
				best_supply_uV, INT_MAX, state);
		if (ret) {
			dev_err(&rdev->dev, "Failed to increase supply voltage: %d\n",
					ret);
			goto out2;
		}
	}

	if (state == PM_SUSPEND_ON)
		ret = _regulator_do_set_voltage(rdev, min_uV, max_uV);
	else
		ret = _regulator_do_set_suspend_voltage(rdev, min_uV,
							max_uV, state);
	if (ret < 0)
		goto out2;

	if (supply_change_uV < 0) {
		ret = regulator_set_voltage_unlocked(rdev->supply,
				best_supply_uV, INT_MAX, state);
		if (ret)
			dev_warn(&rdev->dev, "Failed to decrease supply voltage: %d\n",
					ret);
		/* No need to fail here */
		ret = 0;
	}

out:
	return ret;
out2:
	voltage->min_uV = old_min_uV;
	voltage->max_uV = old_max_uV;

	return ret;
}