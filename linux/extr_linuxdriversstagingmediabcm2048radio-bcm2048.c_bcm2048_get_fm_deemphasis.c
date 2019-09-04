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
struct bcm2048_device {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int BCM2048_DE_EMPHASIS_50us ; 
 int BCM2048_DE_EMPHASIS_75us ; 
 int BCM2048_DE_EMPHASIS_SELECT ; 
 int /*<<< orphan*/  BCM2048_I2C_FM_AUDIO_CTRL0 ; 
 int bcm2048_recv_command (struct bcm2048_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_get_fm_deemphasis(struct bcm2048_device *bdev)
{
	int err;
	u8 value;

	mutex_lock(&bdev->mutex);

	err = bcm2048_recv_command(bdev, BCM2048_I2C_FM_AUDIO_CTRL0, &value);

	mutex_unlock(&bdev->mutex);

	if (!err) {
		if (value & BCM2048_DE_EMPHASIS_SELECT)
			return BCM2048_DE_EMPHASIS_75us;

		return BCM2048_DE_EMPHASIS_50us;
	}

	return err;
}