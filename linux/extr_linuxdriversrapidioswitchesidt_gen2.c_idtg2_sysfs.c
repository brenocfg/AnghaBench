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
struct device {int dummy; } ;
struct rio_dev {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_errlog ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int device_create_file (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int idtg2_sysfs(struct rio_dev *rdev, bool create)
{
	struct device *dev = &rdev->dev;
	int err = 0;

	if (create) {
		/* Initialize sysfs entries */
		err = device_create_file(dev, &dev_attr_errlog);
		if (err)
			dev_err(dev, "Unable create sysfs errlog file\n");
	} else
		device_remove_file(dev, &dev_attr_errlog);

	return err;
}