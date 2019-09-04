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
struct bcm2048_device {scalar_t__ cache_fm_rds_system; int /*<<< orphan*/  rds_info; scalar_t__ rds_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2048_I2C_FM_RDS_MASK1 ; 
 int /*<<< orphan*/  BCM2048_I2C_FM_RDS_SYSTEM ; 
 scalar_t__ BCM2048_RDS_FLAG_FIFO_WLINE ; 
 scalar_t__ BCM2048_RDS_ON ; 
 int bcm2048_send_command (struct bcm2048_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bcm2048_set_rds_no_lock(struct bcm2048_device *bdev, u8 rds_on)
{
	int err;
	u8 flags;

	bdev->cache_fm_rds_system &= ~BCM2048_RDS_ON;

	if (rds_on) {
		bdev->cache_fm_rds_system |= BCM2048_RDS_ON;
		bdev->rds_state = BCM2048_RDS_ON;
		flags =	BCM2048_RDS_FLAG_FIFO_WLINE;
		err = bcm2048_send_command(bdev, BCM2048_I2C_FM_RDS_MASK1,
					   flags);
	} else {
		flags =	0;
		bdev->rds_state = 0;
		err = bcm2048_send_command(bdev, BCM2048_I2C_FM_RDS_MASK1,
					   flags);
		memset(&bdev->rds_info, 0, sizeof(bdev->rds_info));
	}
	if (err)
		return err;

	return bcm2048_send_command(bdev, BCM2048_I2C_FM_RDS_SYSTEM,
				    bdev->cache_fm_rds_system);
}