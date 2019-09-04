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
struct bcm2048_device {scalar_t__ users; scalar_t__ rd_index; scalar_t__ rds_data_available; int /*<<< orphan*/  read_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2048_DEFAULT_MUTE ; 
 int BCM2048_DEFAULT_RDS_WLINE ; 
 int /*<<< orphan*/  BCM2048_DEFAULT_REGION ; 
 int /*<<< orphan*/  BCM2048_DEFAULT_RSSI_THRESHOLD ; 
 int /*<<< orphan*/  BCM2048_ITEM_ENABLED ; 
 int /*<<< orphan*/  BCM2048_POWER_OFF ; 
 int /*<<< orphan*/  BCM2048_POWER_ON ; 
 int bcm2048_checkrev (struct bcm2048_device*) ; 
 int bcm2048_get_rds_wline (struct bcm2048_device*) ; 
 int bcm2048_set_fm_automatic_stereo_mono (struct bcm2048_device*,int /*<<< orphan*/ ) ; 
 int bcm2048_set_fm_search_rssi_threshold (struct bcm2048_device*,int /*<<< orphan*/ ) ; 
 int bcm2048_set_mute (struct bcm2048_device*,int /*<<< orphan*/ ) ; 
 int bcm2048_set_power_state (struct bcm2048_device*,int /*<<< orphan*/ ) ; 
 int bcm2048_set_rds_wline (struct bcm2048_device*,int) ; 
 int bcm2048_set_region (struct bcm2048_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_probe(struct bcm2048_device *bdev)
{
	int err;

	err = bcm2048_set_power_state(bdev, BCM2048_POWER_ON);
	if (err < 0)
		goto unlock;

	err = bcm2048_checkrev(bdev);
	if (err < 0)
		goto unlock;

	err = bcm2048_set_mute(bdev, BCM2048_DEFAULT_MUTE);
	if (err < 0)
		goto unlock;

	err = bcm2048_set_region(bdev, BCM2048_DEFAULT_REGION);
	if (err < 0)
		goto unlock;

	err = bcm2048_set_fm_search_rssi_threshold(bdev,
					BCM2048_DEFAULT_RSSI_THRESHOLD);
	if (err < 0)
		goto unlock;

	err = bcm2048_set_fm_automatic_stereo_mono(bdev, BCM2048_ITEM_ENABLED);
	if (err < 0)
		goto unlock;

	err = bcm2048_get_rds_wline(bdev);
	if (err < BCM2048_DEFAULT_RDS_WLINE)
		err = bcm2048_set_rds_wline(bdev, BCM2048_DEFAULT_RDS_WLINE);
	if (err < 0)
		goto unlock;

	err = bcm2048_set_power_state(bdev, BCM2048_POWER_OFF);

	init_waitqueue_head(&bdev->read_queue);
	bdev->rds_data_available = 0;
	bdev->rd_index = 0;
	bdev->users = 0;

unlock:
	return err;
}