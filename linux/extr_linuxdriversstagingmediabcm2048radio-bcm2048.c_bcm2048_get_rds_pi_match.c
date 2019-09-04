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
struct bcm2048_device {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2048_I2C_RDS_PI_MATCH0 ; 
 int /*<<< orphan*/  BCM2048_I2C_RDS_PI_MATCH1 ; 
 int bcm2048_recv_command (struct bcm2048_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int compose_u16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_get_rds_pi_match(struct bcm2048_device *bdev)
{
	int err;
	u8 lsb = 0, msb = 0;

	mutex_lock(&bdev->mutex);

	err = bcm2048_recv_command(bdev, BCM2048_I2C_RDS_PI_MATCH0, &lsb);
	err |= bcm2048_recv_command(bdev, BCM2048_I2C_RDS_PI_MATCH1, &msb);

	mutex_unlock(&bdev->mutex);

	if (!err)
		return compose_u16(msb, lsb);

	return err;
}