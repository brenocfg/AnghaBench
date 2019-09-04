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
struct ar9170 {int /*<<< orphan*/  udev; int /*<<< orphan*/  fw_load_wait; } ;

/* Variables and functions */
 int carl9170_parse_firmware (struct ar9170*) ; 
 int carl9170_register (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_release_firmware (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_usb_cancel_urbs (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_usb_firmware_failed (struct ar9170*) ; 
 int carl9170_usb_init_device (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_usb_stop (struct ar9170*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void carl9170_usb_firmware_finish(struct ar9170 *ar)
{
	int err;

	err = carl9170_parse_firmware(ar);
	if (err)
		goto err_freefw;

	err = carl9170_usb_init_device(ar);
	if (err)
		goto err_freefw;

	err = carl9170_register(ar);

	carl9170_usb_stop(ar);
	if (err)
		goto err_unrx;

	complete(&ar->fw_load_wait);
	usb_put_dev(ar->udev);
	return;

err_unrx:
	carl9170_usb_cancel_urbs(ar);

err_freefw:
	carl9170_release_firmware(ar);
	carl9170_usb_firmware_failed(ar);
}