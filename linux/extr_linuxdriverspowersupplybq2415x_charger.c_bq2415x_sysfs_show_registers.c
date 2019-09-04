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
struct power_supply {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct bq2415x_device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BQ2415X_REG_CONTROL ; 
 int /*<<< orphan*/  BQ2415X_REG_CURRENT ; 
 int /*<<< orphan*/  BQ2415X_REG_STATUS ; 
 int /*<<< orphan*/  BQ2415X_REG_VENDER ; 
 int /*<<< orphan*/  BQ2415X_REG_VOLTAGE ; 
 int bq2415x_sysfs_print_reg (struct bq2415x_device*,int /*<<< orphan*/ ,char*) ; 
 struct power_supply* dev_get_drvdata (struct device*) ; 
 struct bq2415x_device* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static ssize_t bq2415x_sysfs_show_registers(struct device *dev,
					    struct device_attribute *attr,
					    char *buf)
{
	struct power_supply *psy = dev_get_drvdata(dev);
	struct bq2415x_device *bq = power_supply_get_drvdata(psy);
	ssize_t ret = 0;

	ret += bq2415x_sysfs_print_reg(bq, BQ2415X_REG_STATUS, buf+ret);
	ret += bq2415x_sysfs_print_reg(bq, BQ2415X_REG_CONTROL, buf+ret);
	ret += bq2415x_sysfs_print_reg(bq, BQ2415X_REG_VOLTAGE, buf+ret);
	ret += bq2415x_sysfs_print_reg(bq, BQ2415X_REG_VENDER, buf+ret);
	ret += bq2415x_sysfs_print_reg(bq, BQ2415X_REG_CURRENT, buf+ret);
	return ret;
}