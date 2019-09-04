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
struct lcd_device {int /*<<< orphan*/  ops_lock; TYPE_1__* ops; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_power ) (struct lcd_device*,unsigned long) ;} ;

/* Variables and functions */
 int ENXIO ; 
 int kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct lcd_device*,unsigned long) ; 
 struct lcd_device* to_lcd_device (struct device*) ; 

__attribute__((used)) static ssize_t lcd_power_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	int rc;
	struct lcd_device *ld = to_lcd_device(dev);
	unsigned long power;

	rc = kstrtoul(buf, 0, &power);
	if (rc)
		return rc;

	rc = -ENXIO;

	mutex_lock(&ld->ops_lock);
	if (ld->ops && ld->ops->set_power) {
		pr_debug("set power to %lu\n", power);
		ld->ops->set_power(ld, power);
		rc = count;
	}
	mutex_unlock(&ld->ops_lock);

	return rc;
}