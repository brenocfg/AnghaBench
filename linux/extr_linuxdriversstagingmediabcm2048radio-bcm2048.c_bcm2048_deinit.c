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
struct bcm2048_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2048_POWER_OFF ; 
 int bcm2048_set_audio_route (struct bcm2048_device*,int /*<<< orphan*/ ) ; 
 int bcm2048_set_dac_output (struct bcm2048_device*,int /*<<< orphan*/ ) ; 
 int bcm2048_set_power_state (struct bcm2048_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2048_deinit(struct bcm2048_device *bdev)
{
	int err;

	err = bcm2048_set_audio_route(bdev, 0);
	if (err < 0)
		return err;

	err = bcm2048_set_dac_output(bdev, 0);
	if (err < 0)
		return err;

	return bcm2048_set_power_state(bdev, BCM2048_POWER_OFF);
}