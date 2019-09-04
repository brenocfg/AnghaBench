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
struct rt2x00_dev {int /*<<< orphan*/  flags; scalar_t__ intf_associated; scalar_t__ intf_sta_count; scalar_t__ intf_ap_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_STATE_STARTED ; 
 int rt2x00lib_enable_radio (struct rt2x00_dev*) ; 
 int rt2x00lib_initialize (struct rt2x00_dev*) ; 
 int rt2x00lib_load_firmware (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int rt2x00lib_start(struct rt2x00_dev *rt2x00dev)
{
	int retval;

	if (test_bit(DEVICE_STATE_STARTED, &rt2x00dev->flags))
		return 0;

	/*
	 * If this is the first interface which is added,
	 * we should load the firmware now.
	 */
	retval = rt2x00lib_load_firmware(rt2x00dev);
	if (retval)
		return retval;

	/*
	 * Initialize the device.
	 */
	retval = rt2x00lib_initialize(rt2x00dev);
	if (retval)
		return retval;

	rt2x00dev->intf_ap_count = 0;
	rt2x00dev->intf_sta_count = 0;
	rt2x00dev->intf_associated = 0;

	/* Enable the radio */
	retval = rt2x00lib_enable_radio(rt2x00dev);
	if (retval)
		return retval;

	set_bit(DEVICE_STATE_STARTED, &rt2x00dev->flags);

	return 0;
}