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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int deemphasis; } ;
struct bcm2048_device {int /*<<< orphan*/  mutex; TYPE_1__ region_info; int /*<<< orphan*/  cache_fm_audio_ctrl0; } ;

/* Variables and functions */
 int BCM2048_DE_EMPHASIS_75us ; 
 int /*<<< orphan*/  BCM2048_DE_EMPHASIS_SELECT ; 
 int /*<<< orphan*/  BCM2048_I2C_FM_AUDIO_CTRL0 ; 
 int bcm2048_send_command (struct bcm2048_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_set_fm_deemphasis(struct bcm2048_device *bdev, int d)
{
	int err;
	u8 deemphasis;

	if (d == BCM2048_DE_EMPHASIS_75us)
		deemphasis = BCM2048_DE_EMPHASIS_SELECT;
	else
		deemphasis = 0;

	mutex_lock(&bdev->mutex);

	bdev->cache_fm_audio_ctrl0 &= ~BCM2048_DE_EMPHASIS_SELECT;
	bdev->cache_fm_audio_ctrl0 |= deemphasis;

	err = bcm2048_send_command(bdev, BCM2048_I2C_FM_AUDIO_CTRL0,
				   bdev->cache_fm_audio_ctrl0);

	if (!err)
		bdev->region_info.deemphasis = d;

	mutex_unlock(&bdev->mutex);

	return err;
}