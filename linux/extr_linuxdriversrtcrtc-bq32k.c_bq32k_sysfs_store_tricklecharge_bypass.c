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
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BQ32K_CFG2 ; 
 int BQ32K_TCFE ; 
 int EINVAL ; 
 int bq32k_read (struct device*,int*,int /*<<< orphan*/ ,int) ; 
 int bq32k_write (struct device*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 scalar_t__ kstrtoint (char const*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static ssize_t bq32k_sysfs_store_tricklecharge_bypass(struct device *dev,
						struct device_attribute *attr,
						const char *buf, size_t count)
{
	int reg, enable, error;

	if (kstrtoint(buf, 0, &enable))
		return -EINVAL;

	error = bq32k_read(dev, &reg, BQ32K_CFG2, 1);
	if (error)
		return error;

	if (enable) {
		reg |= BQ32K_TCFE;
		error = bq32k_write(dev, &reg, BQ32K_CFG2, 1);
		if (error)
			return error;

		dev_info(dev, "Enabled trickle charge FET bypass.\n");
	} else {
		reg &= ~BQ32K_TCFE;
		error = bq32k_write(dev, &reg, BQ32K_CFG2, 1);
		if (error)
			return error;

		dev_info(dev, "Disabled trickle charge FET bypass.\n");
	}

	return count;
}