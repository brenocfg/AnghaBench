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
struct userspace_consumer_data {int enabled; int /*<<< orphan*/  lock; int /*<<< orphan*/  supplies; int /*<<< orphan*/  num_supplies; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct userspace_consumer_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sysfs_streq (char const*,char*) ; 

__attribute__((used)) static ssize_t reg_set_state(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct userspace_consumer_data *data = dev_get_drvdata(dev);
	bool enabled;
	int ret;

	/*
	 * sysfs_streq() doesn't need the \n's, but we add them so the strings
	 * will be shared with show_state(), above.
	 */
	if (sysfs_streq(buf, "enabled\n") || sysfs_streq(buf, "1"))
		enabled = true;
	else if (sysfs_streq(buf, "disabled\n") || sysfs_streq(buf, "0"))
		enabled = false;
	else {
		dev_err(dev, "Configuring invalid mode\n");
		return count;
	}

	mutex_lock(&data->lock);
	if (enabled != data->enabled) {
		if (enabled)
			ret = regulator_bulk_enable(data->num_supplies,
						    data->supplies);
		else
			ret = regulator_bulk_disable(data->num_supplies,
						     data->supplies);

		if (ret == 0)
			data->enabled = enabled;
		else
			dev_err(dev, "Failed to configure state: %d\n", ret);
	}
	mutex_unlock(&data->lock);

	return count;
}