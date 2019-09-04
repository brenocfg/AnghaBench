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
struct toshiba_bluetooth_dev {int /*<<< orphan*/  killswitch; int /*<<< orphan*/  rfk; } ;
struct rfkill {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 
 scalar_t__ toshiba_bluetooth_sync_status (struct toshiba_bluetooth_dev*) ; 

__attribute__((used)) static void bt_rfkill_poll(struct rfkill *rfkill, void *data)
{
	struct toshiba_bluetooth_dev *bt_dev = data;

	if (toshiba_bluetooth_sync_status(bt_dev))
		return;

	/*
	 * Note the Toshiba Bluetooth RFKill switch seems to be a strange
	 * fish. It only provides a BT event when the switch is flipped to
	 * the 'on' position. When flipping it to 'off', the USB device is
	 * simply pulled away underneath us, without any BT event being
	 * delivered.
	 */
	rfkill_set_hw_state(bt_dev->rfk, !bt_dev->killswitch);
}