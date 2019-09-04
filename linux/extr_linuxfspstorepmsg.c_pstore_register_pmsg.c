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
struct device {int /*<<< orphan*/  devnode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct device*) ; 
 int /*<<< orphan*/  MKDEV (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMSG_NAME ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 struct device* class_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_destroy (struct device*) ; 
 struct device* device_create (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* pmsg_class ; 
 int /*<<< orphan*/  pmsg_devnode ; 
 int /*<<< orphan*/  pmsg_fops ; 
 scalar_t__ pmsg_major ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ register_chrdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_chrdev (scalar_t__,int /*<<< orphan*/ ) ; 

void pstore_register_pmsg(void)
{
	struct device *pmsg_device;

	pmsg_major = register_chrdev(0, PMSG_NAME, &pmsg_fops);
	if (pmsg_major < 0) {
		pr_err("register_chrdev failed\n");
		goto err;
	}

	pmsg_class = class_create(THIS_MODULE, PMSG_NAME);
	if (IS_ERR(pmsg_class)) {
		pr_err("device class file already in use\n");
		goto err_class;
	}
	pmsg_class->devnode = pmsg_devnode;

	pmsg_device = device_create(pmsg_class, NULL, MKDEV(pmsg_major, 0),
					NULL, "%s%d", PMSG_NAME, 0);
	if (IS_ERR(pmsg_device)) {
		pr_err("failed to create device\n");
		goto err_device;
	}
	return;

err_device:
	class_destroy(pmsg_class);
err_class:
	unregister_chrdev(pmsg_major, PMSG_NAME);
err:
	return;
}