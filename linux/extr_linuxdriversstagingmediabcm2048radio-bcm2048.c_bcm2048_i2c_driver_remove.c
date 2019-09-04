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
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  adapter; } ;
struct bcm2048_device {int /*<<< orphan*/  work; scalar_t__ power_state; int /*<<< orphan*/  videodev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BCM2048_POWER_OFF ; 
 int ENODEV ; 
 int /*<<< orphan*/  attrs ; 
 int /*<<< orphan*/  bcm2048_set_power_state (struct bcm2048_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm2048_sysfs_unregister_properties (struct bcm2048_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct bcm2048_device*) ; 
 struct bcm2048_device* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct bcm2048_device*) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_i2c_driver_remove(struct i2c_client *client)
{
	struct bcm2048_device *bdev = i2c_get_clientdata(client);

	if (!client->adapter)
		return -ENODEV;

	if (bdev) {
		bcm2048_sysfs_unregister_properties(bdev, ARRAY_SIZE(attrs));
		video_unregister_device(&bdev->videodev);

		if (bdev->power_state)
			bcm2048_set_power_state(bdev, BCM2048_POWER_OFF);

		if (client->irq > 0)
			free_irq(client->irq, bdev);

		cancel_work_sync(&bdev->work);

		kfree(bdev);
	}

	return 0;
}