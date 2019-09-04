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
struct bcm2048_device {int /*<<< orphan*/  mutex; } ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2048_I2C_FM_CARRIER ; 
 int bcm2048_recv_command (struct bcm2048_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_get_fm_carrier_error(struct bcm2048_device *bdev)
{
	int err = 0;
	s8 value;

	mutex_lock(&bdev->mutex);
	err = bcm2048_recv_command(bdev, BCM2048_I2C_FM_CARRIER, &value);
	mutex_unlock(&bdev->mutex);

	if (!err)
		return value;

	return err;
}