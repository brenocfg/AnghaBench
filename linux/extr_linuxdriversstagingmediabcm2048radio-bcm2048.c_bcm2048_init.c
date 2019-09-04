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
 int /*<<< orphan*/  BCM2048_AUDIO_ROUTE_DAC ; 
 int BCM2048_DAC_OUTPUT_LEFT ; 
 int BCM2048_DAC_OUTPUT_RIGHT ; 
 int /*<<< orphan*/  BCM2048_POWER_ON ; 
 int bcm2048_set_audio_route (struct bcm2048_device*,int /*<<< orphan*/ ) ; 
 int bcm2048_set_dac_output (struct bcm2048_device*,int) ; 
 int bcm2048_set_power_state (struct bcm2048_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2048_init(struct bcm2048_device *bdev)
{
	int err;

	err = bcm2048_set_power_state(bdev, BCM2048_POWER_ON);
	if (err < 0)
		goto exit;

	err = bcm2048_set_audio_route(bdev, BCM2048_AUDIO_ROUTE_DAC);
	if (err < 0)
		goto exit;

	err = bcm2048_set_dac_output(bdev, BCM2048_DAC_OUTPUT_LEFT |
				     BCM2048_DAC_OUTPUT_RIGHT);

exit:
	return err;
}