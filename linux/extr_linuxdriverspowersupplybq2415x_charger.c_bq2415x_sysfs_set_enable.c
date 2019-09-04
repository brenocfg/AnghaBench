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
struct power_supply {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct device {int dummy; } ;
struct bq2415x_device {int dummy; } ;
typedef  int ssize_t ;
typedef  enum bq2415x_command { ____Placeholder_bq2415x_command } bq2415x_command ;

/* Variables and functions */
 int BQ2415X_CHARGE_TERMINATION_DISABLE ; 
 int BQ2415X_CHARGE_TERMINATION_ENABLE ; 
 int BQ2415X_HIGH_IMPEDANCE_DISABLE ; 
 int BQ2415X_HIGH_IMPEDANCE_ENABLE ; 
 int BQ2415X_OTG_PIN_DISABLE ; 
 int BQ2415X_OTG_PIN_ENABLE ; 
 int BQ2415X_STAT_PIN_DISABLE ; 
 int BQ2415X_STAT_PIN_ENABLE ; 
 int EINVAL ; 
 int bq2415x_exec_command (struct bq2415x_device*,int) ; 
 struct power_supply* dev_get_drvdata (struct device*) ; 
 scalar_t__ kstrtol (char const*,int,long*) ; 
 struct bq2415x_device* power_supply_get_drvdata (struct power_supply*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t bq2415x_sysfs_set_enable(struct device *dev,
					struct device_attribute *attr,
					const char *buf,
					size_t count)
{
	struct power_supply *psy = dev_get_drvdata(dev);
	struct bq2415x_device *bq = power_supply_get_drvdata(psy);
	enum bq2415x_command command;
	long val;
	int ret;

	if (kstrtol(buf, 10, &val) < 0)
		return -EINVAL;

	if (strcmp(attr->attr.name, "charge_termination_enable") == 0)
		command = val ? BQ2415X_CHARGE_TERMINATION_ENABLE :
			BQ2415X_CHARGE_TERMINATION_DISABLE;
	else if (strcmp(attr->attr.name, "high_impedance_enable") == 0)
		command = val ? BQ2415X_HIGH_IMPEDANCE_ENABLE :
			BQ2415X_HIGH_IMPEDANCE_DISABLE;
	else if (strcmp(attr->attr.name, "otg_pin_enable") == 0)
		command = val ? BQ2415X_OTG_PIN_ENABLE :
			BQ2415X_OTG_PIN_DISABLE;
	else if (strcmp(attr->attr.name, "stat_pin_enable") == 0)
		command = val ? BQ2415X_STAT_PIN_ENABLE :
			BQ2415X_STAT_PIN_DISABLE;
	else
		return -EINVAL;

	ret = bq2415x_exec_command(bq, command);
	if (ret < 0)
		return ret;
	return count;
}