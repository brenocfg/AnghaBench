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
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void skl_nhlt_remove_sysfs(struct skl_dev *skl)
{
	struct device *dev = &skl->pci->dev;

	sysfs_remove_file(&dev->kobj, &dev_attr_platform_id.attr);
}