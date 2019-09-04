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
struct serdev_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_serdev_device_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct serdev_device**) ; 
 struct serdev_device** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct serdev_device**) ; 
 int serdev_device_open (struct serdev_device*) ; 

int devm_serdev_device_open(struct device *dev, struct serdev_device *serdev)
{
	struct serdev_device **dr;
	int ret;

	dr = devres_alloc(devm_serdev_device_release, sizeof(*dr), GFP_KERNEL);
	if (!dr)
		return -ENOMEM;

	ret = serdev_device_open(serdev);
	if (ret) {
		devres_free(dr);
		return ret;
	}

	*dr = serdev;
	devres_add(dev, dr);

	return 0;
}