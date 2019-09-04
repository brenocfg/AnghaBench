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
struct ar9170 {int cmd_seq; int /*<<< orphan*/  usb_tasklet; TYPE_1__* intf; } ;
struct TYPE_2__ {scalar_t__ condition; } ;

/* Variables and functions */
 scalar_t__ USB_INTERFACE_BOUND ; 
 int carl9170_reboot (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_usb_cancel_urbs (struct ar9170*) ; 
 int carl9170_usb_load_firmware (struct ar9170*) ; 
 int carl9170_usb_open (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_usb_stop (struct ar9170*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

int carl9170_usb_restart(struct ar9170 *ar)
{
	int err = 0;

	if (ar->intf->condition != USB_INTERFACE_BOUND)
		return 0;

	/*
	 * Disable the command response sequence counter check.
	 * We already know that the device/firmware is in a bad state.
	 * So, no extra points are awarded to anyone who reminds the
	 * driver about that.
	 */
	ar->cmd_seq = -2;

	err = carl9170_reboot(ar);

	carl9170_usb_stop(ar);

	if (err)
		goto err_out;

	tasklet_schedule(&ar->usb_tasklet);

	/* The reboot procedure can take quite a while to complete. */
	msleep(1100);

	err = carl9170_usb_open(ar);
	if (err)
		goto err_out;

	err = carl9170_usb_load_firmware(ar);
	if (err)
		goto err_out;

	return 0;

err_out:
	carl9170_usb_cancel_urbs(ar);
	return err;
}