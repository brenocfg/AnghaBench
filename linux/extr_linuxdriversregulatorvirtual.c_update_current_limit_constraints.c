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
struct virtual_consumer_data {scalar_t__ max_uA; scalar_t__ min_uA; int enabled; int /*<<< orphan*/  regulator; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int regulator_set_current_limit (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void update_current_limit_constraints(struct device *dev,
					  struct virtual_consumer_data *data)
{
	int ret;

	if (data->max_uA
	    && data->min_uA <= data->max_uA) {
		dev_dbg(dev, "Requesting %d-%duA\n",
			data->min_uA, data->max_uA);
		ret = regulator_set_current_limit(data->regulator,
					data->min_uA, data->max_uA);
		if (ret != 0) {
			dev_err(dev,
				"regulator_set_current_limit() failed: %d\n",
				ret);
			return;
		}
	}

	if (data->max_uA && !data->enabled) {
		dev_dbg(dev, "Enabling regulator\n");
		ret = regulator_enable(data->regulator);
		if (ret == 0)
			data->enabled = true;
		else
			dev_err(dev, "regulator_enable() failed: %d\n",
				ret);
	}

	if (!(data->min_uA && data->max_uA) && data->enabled) {
		dev_dbg(dev, "Disabling regulator\n");
		ret = regulator_disable(data->regulator);
		if (ret == 0)
			data->enabled = false;
		else
			dev_err(dev, "regulator_disable() failed: %d\n",
				ret);
	}
}