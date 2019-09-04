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
struct uio_device {int /*<<< orphan*/  info_lock; TYPE_1__* info; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct uio_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t name_show(struct device *dev,
			 struct device_attribute *attr, char *buf)
{
	struct uio_device *idev = dev_get_drvdata(dev);
	int ret;

	mutex_lock(&idev->info_lock);
	if (!idev->info) {
		ret = -EINVAL;
		dev_err(dev, "the device has been unregistered\n");
		goto out;
	}

	ret = sprintf(buf, "%s\n", idev->info->name);

out:
	mutex_unlock(&idev->info_lock);
	return ret;
}