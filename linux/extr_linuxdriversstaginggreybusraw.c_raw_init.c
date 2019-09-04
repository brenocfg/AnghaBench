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
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUM_MINORS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  class_create (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gb_raw_driver ; 
 int greybus_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_class ; 
 int /*<<< orphan*/  raw_major ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int raw_init(void)
{
	dev_t dev;
	int retval;

	raw_class = class_create(THIS_MODULE, "gb_raw");
	if (IS_ERR(raw_class)) {
		retval = PTR_ERR(raw_class);
		goto error_class;
	}

	retval = alloc_chrdev_region(&dev, 0, NUM_MINORS, "gb_raw");
	if (retval < 0)
		goto error_chrdev;

	raw_major = MAJOR(dev);

	retval = greybus_register(&gb_raw_driver);
	if (retval)
		goto error_gb;

	return 0;

error_gb:
	unregister_chrdev_region(dev, NUM_MINORS);
error_chrdev:
	class_destroy(raw_class);
error_class:
	return retval;
}