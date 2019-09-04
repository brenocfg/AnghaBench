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
typedef  int /*<<< orphan*/  u8 ;
struct bcm2048_device {int /*<<< orphan*/  mutex; int /*<<< orphan*/  cache_fm_search_ctrl0; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2048_I2C_FM_SEARCH_CTRL0 ; 
 int /*<<< orphan*/  BCM2048_SEARCH_RSSI_THRESHOLD ; 
 int bcm2048_send_command (struct bcm2048_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_set_fm_search_rssi_threshold(struct bcm2048_device *bdev,
						u8 threshold)
{
	int err;

	mutex_lock(&bdev->mutex);

	threshold &= BCM2048_SEARCH_RSSI_THRESHOLD;
	bdev->cache_fm_search_ctrl0 &= ~BCM2048_SEARCH_RSSI_THRESHOLD;
	bdev->cache_fm_search_ctrl0 |= threshold;

	err = bcm2048_send_command(bdev, BCM2048_I2C_FM_SEARCH_CTRL0,
				   bdev->cache_fm_search_ctrl0);

	mutex_unlock(&bdev->mutex);
	return err;
}