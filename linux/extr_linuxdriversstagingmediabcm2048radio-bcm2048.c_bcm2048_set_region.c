#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct TYPE_3__ {int bottom_frequency; int top_frequency; int /*<<< orphan*/  deemphasis; } ;
struct bcm2048_device {int frequency; int /*<<< orphan*/  mutex; int /*<<< orphan*/  cache_fm_ctrl; TYPE_1__ region_info; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  BCM2048_BAND_SELECT ; 
 int /*<<< orphan*/  BCM2048_I2C_FM_CTRL ; 
 int EINVAL ; 
 int bcm2048_send_command (struct bcm2048_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bcm2048_set_fm_deemphasis (struct bcm2048_device*,int /*<<< orphan*/ ) ; 
 int bcm2048_set_fm_frequency (struct bcm2048_device*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* region_configs ; 

__attribute__((used)) static int bcm2048_set_region(struct bcm2048_device *bdev, u8 region)
{
	int err;
	u32 new_frequency = 0;

	if (region >= ARRAY_SIZE(region_configs))
		return -EINVAL;

	mutex_lock(&bdev->mutex);
	bdev->region_info = region_configs[region];

	if (region_configs[region].bottom_frequency < 87500)
		bdev->cache_fm_ctrl |= BCM2048_BAND_SELECT;
	else
		bdev->cache_fm_ctrl &= ~BCM2048_BAND_SELECT;

	err = bcm2048_send_command(bdev, BCM2048_I2C_FM_CTRL,
				   bdev->cache_fm_ctrl);
	if (err) {
		mutex_unlock(&bdev->mutex);
		goto done;
	}
	mutex_unlock(&bdev->mutex);

	if (bdev->frequency < region_configs[region].bottom_frequency ||
	    bdev->frequency > region_configs[region].top_frequency)
		new_frequency = region_configs[region].bottom_frequency;

	if (new_frequency > 0) {
		err = bcm2048_set_fm_frequency(bdev, new_frequency);

		if (err)
			goto done;
	}

	err = bcm2048_set_fm_deemphasis(bdev,
					region_configs[region].deemphasis);

done:
	return err;
}