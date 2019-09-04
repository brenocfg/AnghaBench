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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {scalar_t__ bottom_frequency; scalar_t__ top_frequency; } ;
struct bcm2048_device {int /*<<< orphan*/  mutex; scalar_t__ frequency; TYPE_1__ region_info; } ;

/* Variables and functions */
 scalar_t__ BCM2048_FREQUENCY_BASE ; 
 int /*<<< orphan*/  BCM2048_I2C_FM_FREQ0 ; 
 int /*<<< orphan*/  BCM2048_I2C_FM_FREQ1 ; 
 int EDOM ; 
 int bcm2048_send_command (struct bcm2048_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsb (scalar_t__) ; 
 int /*<<< orphan*/  msb (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bcm2048_set_fm_frequency(struct bcm2048_device *bdev, u32 frequency)
{
	int err;

	if (frequency < bdev->region_info.bottom_frequency ||
	    frequency > bdev->region_info.top_frequency)
		return -EDOM;

	frequency -= BCM2048_FREQUENCY_BASE;

	mutex_lock(&bdev->mutex);

	err = bcm2048_send_command(bdev, BCM2048_I2C_FM_FREQ0, lsb(frequency));
	err |= bcm2048_send_command(bdev, BCM2048_I2C_FM_FREQ1,
				    msb(frequency));

	if (!err)
		bdev->frequency = frequency;

	mutex_unlock(&bdev->mutex);
	return err;
}