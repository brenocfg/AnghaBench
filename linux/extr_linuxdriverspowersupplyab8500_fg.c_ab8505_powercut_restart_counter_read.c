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
struct power_supply {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct ab8500_fg {int /*<<< orphan*/  dev; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AB8500_RTC ; 
 int /*<<< orphan*/  AB8505_RTC_PCUT_RESTART_REG ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int abx500_get_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct power_supply* dev_get_drvdata (struct device*) ; 
 struct ab8500_fg* power_supply_get_drvdata (struct power_supply*) ; 
 int scnprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t ab8505_powercut_restart_counter_read(struct device *dev,
						    struct device_attribute *attr,
						    char *buf)
{
	int ret;
	u8 reg_value;
	struct power_supply *psy = dev_get_drvdata(dev);
	struct ab8500_fg *di = power_supply_get_drvdata(psy);

	ret = abx500_get_register_interruptible(di->dev, AB8500_RTC,
						AB8505_RTC_PCUT_RESTART_REG, &reg_value);

	if (ret < 0) {
		dev_err(dev, "Failed to read AB8505_RTC_PCUT_RESTART_REG\n");
		goto fail;
	}

	return scnprintf(buf, PAGE_SIZE, "%d\n", (reg_value & 0xF0) >> 4);

fail:
	return ret;
}