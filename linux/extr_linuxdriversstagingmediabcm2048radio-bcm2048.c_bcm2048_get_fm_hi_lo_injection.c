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
 int BCM2048_HI_LO_INJECTION ; 
 int /*<<< orphan*/  BCM2048_I2C_FM_CTRL ; 
 int BCM2048_ITEM_ENABLED ; 
 int bcm2048_recv_command (struct bcm2048_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_get_fm_hi_lo_injection(struct bcm2048_device *bdev)
{
	int err;
	u8 value;

	mutex_lock(&bdev->mutex);

	err = bcm2048_recv_command(bdev, BCM2048_I2C_FM_CTRL, &value);

	mutex_unlock(&bdev->mutex);

	if (!err && (value & BCM2048_HI_LO_INJECTION))
		return BCM2048_ITEM_ENABLED;

	return err;
}