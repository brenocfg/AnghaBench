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
struct bcm2048_device {int /*<<< orphan*/  mutex; int /*<<< orphan*/  power_state; int /*<<< orphan*/  cache_fm_rds_system; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2048_DEFAULT_POWERING_DELAY ; 
 int /*<<< orphan*/  BCM2048_FM_ON ; 
 int /*<<< orphan*/  BCM2048_I2C_FM_RDS_SYSTEM ; 
 int /*<<< orphan*/  BCM2048_POWER_OFF ; 
 int /*<<< orphan*/  BCM2048_POWER_ON ; 
 int bcm2048_send_command (struct bcm2048_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_set_power_state(struct bcm2048_device *bdev, u8 power)
{
	int err = 0;

	mutex_lock(&bdev->mutex);

	if (power) {
		bdev->power_state = BCM2048_POWER_ON;
		bdev->cache_fm_rds_system |= BCM2048_FM_ON;
	} else {
		bdev->cache_fm_rds_system &= ~BCM2048_FM_ON;
	}

	/*
	 * Warning! FM cannot be turned off because then
	 * the I2C communications get ruined!
	 * Comment off the "if (power)" when the chip works!
	 */
	if (power)
		err = bcm2048_send_command(bdev, BCM2048_I2C_FM_RDS_SYSTEM,
					   bdev->cache_fm_rds_system);
	msleep(BCM2048_DEFAULT_POWERING_DELAY);

	if (!power)
		bdev->power_state = BCM2048_POWER_OFF;

	mutex_unlock(&bdev->mutex);
	return err;
}