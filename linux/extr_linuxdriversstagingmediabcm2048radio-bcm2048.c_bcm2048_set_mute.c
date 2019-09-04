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
typedef  scalar_t__ u16 ;
struct bcm2048_device {int cache_fm_audio_ctrl0; int /*<<< orphan*/  mutex; scalar_t__ mute_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2048_I2C_FM_AUDIO_CTRL0 ; 
 int BCM2048_MANUAL_MUTE ; 
 int BCM2048_RF_MUTE ; 
 int bcm2048_send_command (struct bcm2048_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_set_mute(struct bcm2048_device *bdev, u16 mute)
{
	int err;

	mutex_lock(&bdev->mutex);

	bdev->cache_fm_audio_ctrl0 &= ~(BCM2048_RF_MUTE | BCM2048_MANUAL_MUTE);

	if (mute)
		bdev->cache_fm_audio_ctrl0 |= (BCM2048_RF_MUTE |
					       BCM2048_MANUAL_MUTE);

	err = bcm2048_send_command(bdev, BCM2048_I2C_FM_AUDIO_CTRL0,
				   bdev->cache_fm_audio_ctrl0);

	if (!err)
		bdev->mute_state = mute;

	mutex_unlock(&bdev->mutex);
	return err;
}