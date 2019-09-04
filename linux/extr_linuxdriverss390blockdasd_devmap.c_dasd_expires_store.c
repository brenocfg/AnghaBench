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
struct dasd_device {unsigned long default_expires; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 unsigned long DASD_EXPIRES_MAX ; 
 size_t EINVAL ; 
 size_t ENODEV ; 
 scalar_t__ IS_ERR (struct dasd_device*) ; 
 struct dasd_device* dasd_device_from_cdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dasd_put_device (struct dasd_device*) ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  to_ccwdev (struct device*) ; 

__attribute__((used)) static ssize_t
dasd_expires_store(struct device *dev, struct device_attribute *attr,
	       const char *buf, size_t count)
{
	struct dasd_device *device;
	unsigned long val;

	device = dasd_device_from_cdev(to_ccwdev(dev));
	if (IS_ERR(device))
		return -ENODEV;

	if ((kstrtoul(buf, 10, &val) != 0) ||
	    (val > DASD_EXPIRES_MAX) || val == 0) {
		dasd_put_device(device);
		return -EINVAL;
	}

	if (val)
		device->default_expires = val;

	dasd_put_device(device);
	return count;
}