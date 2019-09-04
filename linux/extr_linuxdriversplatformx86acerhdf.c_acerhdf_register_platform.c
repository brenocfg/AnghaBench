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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  acerhdf_dev ; 
 int /*<<< orphan*/  acerhdf_driver ; 
 int platform_device_add (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_device_alloc (char*,int) ; 
 int /*<<< orphan*/  platform_device_put (int /*<<< orphan*/ ) ; 
 int platform_driver_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_driver_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int acerhdf_register_platform(void)
{
	int err = 0;

	err = platform_driver_register(&acerhdf_driver);
	if (err)
		return err;

	acerhdf_dev = platform_device_alloc("acerhdf", -1);
	if (!acerhdf_dev) {
		err = -ENOMEM;
		goto err_device_alloc;
	}
	err = platform_device_add(acerhdf_dev);
	if (err)
		goto err_device_add;

	return 0;

err_device_add:
	platform_device_put(acerhdf_dev);
err_device_alloc:
	platform_driver_unregister(&acerhdf_driver);
	return err;
}