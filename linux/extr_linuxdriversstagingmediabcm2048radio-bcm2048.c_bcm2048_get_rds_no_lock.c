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
struct bcm2048_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2048_I2C_FM_RDS_SYSTEM ; 
 int BCM2048_ITEM_ENABLED ; 
 int BCM2048_RDS_ON ; 
 int bcm2048_recv_command (struct bcm2048_device*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int bcm2048_get_rds_no_lock(struct bcm2048_device *bdev)
{
	int err;
	u8 value;

	err = bcm2048_recv_command(bdev, BCM2048_I2C_FM_RDS_SYSTEM, &value);

	if (!err && (value & BCM2048_RDS_ON))
		return BCM2048_ITEM_ENABLED;

	return err;
}