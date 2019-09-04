#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct us_data {TYPE_1__* pusb_dev; int /*<<< orphan*/  dflags; int /*<<< orphan*/  pusb_intf; } ;
struct TYPE_4__ {int quirks; } ;

/* Variables and functions */
 int EIO ; 
 int EPERM ; 
 int USB_QUIRK_RESET ; 
 int /*<<< orphan*/  US_FLIDX_DISCONNECTING ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_lock_device_for_reset (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int usb_reset_device (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,...) ; 
 int /*<<< orphan*/  usb_unlock_device (TYPE_1__*) ; 

int usb_stor_port_reset(struct us_data *us)
{
	int result;

	/*for these devices we must use the class specific method */
	if (us->pusb_dev->quirks & USB_QUIRK_RESET)
		return -EPERM;

	result = usb_lock_device_for_reset(us->pusb_dev, us->pusb_intf);
	if (result < 0)
		usb_stor_dbg(us, "unable to lock device for reset: %d\n",
			     result);
	else {
		/* Were we disconnected while waiting for the lock? */
		if (test_bit(US_FLIDX_DISCONNECTING, &us->dflags)) {
			result = -EIO;
			usb_stor_dbg(us, "No reset during disconnect\n");
		} else {
			result = usb_reset_device(us->pusb_dev);
			usb_stor_dbg(us, "usb_reset_device returns %d\n",
				     result);
		}
		usb_unlock_device(us->pusb_dev);
	}
	return result;
}