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
typedef  scalar_t__ u8 ;
struct bcm2048_device {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 scalar_t__ BCM2048_BEST_TUNE_MODE ; 
 int /*<<< orphan*/  BCM2048_I2C_FM_BEST_TUNE_MODE ; 
 int bcm2048_recv_command (struct bcm2048_device*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int bcm2048_send_command (struct bcm2048_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_set_fm_best_tune_mode(struct bcm2048_device *bdev, u8 mode)
{
	int err;
	u8 value = 0;

	mutex_lock(&bdev->mutex);

	/* Perform read as the manual indicates */
	err = bcm2048_recv_command(bdev, BCM2048_I2C_FM_BEST_TUNE_MODE,
				   &value);
	value &= ~BCM2048_BEST_TUNE_MODE;

	if (mode)
		value |= BCM2048_BEST_TUNE_MODE;
	err |= bcm2048_send_command(bdev, BCM2048_I2C_FM_BEST_TUNE_MODE,
				    value);

	mutex_unlock(&bdev->mutex);
	return err;
}