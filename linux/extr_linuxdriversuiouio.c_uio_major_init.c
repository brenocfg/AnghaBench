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
struct cdev {int /*<<< orphan*/  kobj; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  UIO_MAX_DEVICES ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int cdev_add (struct cdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cdev* cdev_alloc () ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_set_name (int /*<<< orphan*/ *,char*,char const*) ; 
 struct cdev* uio_cdev ; 
 int /*<<< orphan*/  uio_fops ; 
 int /*<<< orphan*/  uio_major ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uio_major_init(void)
{
	static const char name[] = "uio";
	struct cdev *cdev = NULL;
	dev_t uio_dev = 0;
	int result;

	result = alloc_chrdev_region(&uio_dev, 0, UIO_MAX_DEVICES, name);
	if (result)
		goto out;

	result = -ENOMEM;
	cdev = cdev_alloc();
	if (!cdev)
		goto out_unregister;

	cdev->owner = THIS_MODULE;
	cdev->ops = &uio_fops;
	kobject_set_name(&cdev->kobj, "%s", name);

	result = cdev_add(cdev, uio_dev, UIO_MAX_DEVICES);
	if (result)
		goto out_put;

	uio_major = MAJOR(uio_dev);
	uio_cdev = cdev;
	return 0;
out_put:
	kobject_put(&cdev->kobj);
out_unregister:
	unregister_chrdev_region(uio_dev, UIO_MAX_DEVICES);
out:
	return result;
}