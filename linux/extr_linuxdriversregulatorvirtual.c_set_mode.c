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
struct virtual_consumer_data {unsigned int mode; int /*<<< orphan*/  lock; int /*<<< orphan*/  regulator; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 unsigned int REGULATOR_MODE_FAST ; 
 unsigned int REGULATOR_MODE_IDLE ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 unsigned int REGULATOR_MODE_STANDBY ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct virtual_consumer_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regulator_set_mode (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ sysfs_streq (char const*,char*) ; 

__attribute__((used)) static ssize_t set_mode(struct device *dev, struct device_attribute *attr,
			const char *buf, size_t count)
{
	struct virtual_consumer_data *data = dev_get_drvdata(dev);
	unsigned int mode;
	int ret;

	/*
	 * sysfs_streq() doesn't need the \n's, but we add them so the strings
	 * will be shared with show_mode(), above.
	 */
	if (sysfs_streq(buf, "fast\n"))
		mode = REGULATOR_MODE_FAST;
	else if (sysfs_streq(buf, "normal\n"))
		mode = REGULATOR_MODE_NORMAL;
	else if (sysfs_streq(buf, "idle\n"))
		mode = REGULATOR_MODE_IDLE;
	else if (sysfs_streq(buf, "standby\n"))
		mode = REGULATOR_MODE_STANDBY;
	else {
		dev_err(dev, "Configuring invalid mode\n");
		return count;
	}

	mutex_lock(&data->lock);
	ret = regulator_set_mode(data->regulator, mode);
	if (ret == 0)
		data->mode = mode;
	else
		dev_err(dev, "Failed to configure mode: %d\n", ret);
	mutex_unlock(&data->lock);

	return count;
}