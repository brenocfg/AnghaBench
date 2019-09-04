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
typedef  int u8 ;
struct bcm2048_device {int mute_state; int /*<<< orphan*/  mutex; scalar_t__ power_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2048_I2C_FM_AUDIO_CTRL0 ; 
 int BCM2048_MANUAL_MUTE ; 
 int BCM2048_RF_MUTE ; 
 int bcm2048_recv_command (struct bcm2048_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_get_mute(struct bcm2048_device *bdev)
{
	int err;
	u8 value;

	mutex_lock(&bdev->mutex);

	if (bdev->power_state) {
		err = bcm2048_recv_command(bdev, BCM2048_I2C_FM_AUDIO_CTRL0,
					   &value);
		if (!err)
			err = value & (BCM2048_RF_MUTE | BCM2048_MANUAL_MUTE);
	} else {
		err = bdev->mute_state;
	}

	mutex_unlock(&bdev->mutex);
	return err;
}