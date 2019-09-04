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
struct toshiba_haps_dev {int protection_level; TYPE_1__* acpi_dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int EINVAL ; 
 struct toshiba_haps_dev* dev_get_drvdata (struct device*) ; 
 int kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 
 int toshiba_haps_protection_level (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ssize_t protection_level_store(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct toshiba_haps_dev *haps = dev_get_drvdata(dev);
	int level;
	int ret;

	ret = kstrtoint(buf, 0, &level);
	if (ret)
		return ret;
	/*
	 * Check for supported levels, which can be:
	 * 0 - Disabled | 1 - Low | 2 - Medium | 3 - High
	 */
	if (level < 0 || level > 3)
		return -EINVAL;

	/* Set the sensor level */
	ret = toshiba_haps_protection_level(haps->acpi_dev->handle, level);
	if (ret != 0)
		return ret;

	haps->protection_level = level;

	return count;
}