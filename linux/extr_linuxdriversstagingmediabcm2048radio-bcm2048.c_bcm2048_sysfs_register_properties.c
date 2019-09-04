#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bcm2048_device {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EBUSY ; 
 int /*<<< orphan*/ * attrs ; 
 int /*<<< orphan*/  bcm2048_sysfs_unregister_properties (struct bcm2048_device*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_sysfs_register_properties(struct bcm2048_device *bdev)
{
	int err = 0;
	int i;

	for (i = 0; i < ARRAY_SIZE(attrs); i++) {
		if (device_create_file(&bdev->client->dev, &attrs[i]) != 0) {
			dev_err(&bdev->client->dev,
				"could not register sysfs entry\n");
			err = -EBUSY;
			bcm2048_sysfs_unregister_properties(bdev, i);
			break;
		}
	}

	return err;
}