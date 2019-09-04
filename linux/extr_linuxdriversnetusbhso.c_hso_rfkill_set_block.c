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
struct hso_device {int /*<<< orphan*/  mutex; int /*<<< orphan*/  usb; scalar_t__ usb_gone; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_rcvctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hso_rfkill_set_block(void *data, bool blocked)
{
	struct hso_device *hso_dev = data;
	int enabled = !blocked;
	int rv;

	mutex_lock(&hso_dev->mutex);
	if (hso_dev->usb_gone)
		rv = 0;
	else
		rv = usb_control_msg(hso_dev->usb, usb_rcvctrlpipe(hso_dev->usb, 0),
				       enabled ? 0x82 : 0x81, 0x40, 0, 0, NULL, 0,
				       USB_CTRL_SET_TIMEOUT);
	mutex_unlock(&hso_dev->mutex);
	return rv;
}