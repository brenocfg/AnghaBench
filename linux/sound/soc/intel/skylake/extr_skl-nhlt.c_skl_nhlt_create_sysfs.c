#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct skl_dev {TYPE_1__* pci; } ;
struct device {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {int /*<<< orphan*/  attr; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 TYPE_2__ dev_attr_platform_id ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 scalar_t__ sysfs_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int skl_nhlt_create_sysfs(struct skl_dev *skl)
{
	struct device *dev = &skl->pci->dev;

	if (sysfs_create_file(&dev->kobj, &dev_attr_platform_id.attr))
		dev_warn(dev, "Error creating sysfs entry\n");

	return 0;
}