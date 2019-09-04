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
struct device {int /*<<< orphan*/  class; int /*<<< orphan*/ * type; } ;
struct hci_dev {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_class ; 
 int /*<<< orphan*/  bt_host ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 

void hci_init_sysfs(struct hci_dev *hdev)
{
	struct device *dev = &hdev->dev;

	dev->type = &bt_host;
	dev->class = bt_class;

	__module_get(THIS_MODULE);
	device_initialize(dev);
}