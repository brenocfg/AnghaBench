#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rt2x00_dev {TYPE_3__* fw; TYPE_2__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_5__ {TYPE_1__* lib; } ;
struct TYPE_4__ {int (* load_firmware ) (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE_FIRMWARE ; 
 int /*<<< orphan*/  rt2x00_has_cap_flag (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00leds_led_assoc (struct rt2x00_dev*,int) ; 
 int rt2x00lib_request_firmware (struct rt2x00_dev*) ; 
 int stub1 (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rt2x00lib_load_firmware(struct rt2x00_dev *rt2x00dev)
{
	int retval;

	if (!rt2x00_has_cap_flag(rt2x00dev, REQUIRE_FIRMWARE))
		return 0;

	if (!rt2x00dev->fw) {
		retval = rt2x00lib_request_firmware(rt2x00dev);
		if (retval)
			return retval;
	}

	/*
	 * Send firmware to the device.
	 */
	retval = rt2x00dev->ops->lib->load_firmware(rt2x00dev,
						    rt2x00dev->fw->data,
						    rt2x00dev->fw->size);

	/*
	 * When the firmware is uploaded to the hardware the LED
	 * association status might have been triggered, for correct
	 * LED handling it should now be reset.
	 */
	rt2x00leds_led_assoc(rt2x00dev, false);

	return retval;
}