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
struct bcm2048_device {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cache_fm_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2048_I2C_FM_CTRL ; 
 int /*<<< orphan*/  BCM2048_STEREO_MONO_AUTO_SELECT ; 
 int bcm2048_send_command (struct bcm2048_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_set_fm_automatic_stereo_mono(struct bcm2048_device *bdev,
						u8 enabled)
{
	int err;

	mutex_lock(&bdev->mutex);

	bdev->cache_fm_ctrl &= ~BCM2048_STEREO_MONO_AUTO_SELECT;

	if (enabled)
		bdev->cache_fm_ctrl |= BCM2048_STEREO_MONO_AUTO_SELECT;

	err = bcm2048_send_command(bdev, BCM2048_I2C_FM_CTRL,
				   bdev->cache_fm_ctrl);

	mutex_unlock(&bdev->mutex);
	return err;
}