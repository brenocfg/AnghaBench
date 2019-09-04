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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_BAD ; 
 int NOTIFY_OK ; 
#define  USB_BUS_ADD 131 
#define  USB_BUS_REMOVE 130 
#define  USB_DEVICE_ADD 129 
#define  USB_DEVICE_REMOVE 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  wusb_dev_add_ncb (void*) ; 
 int /*<<< orphan*/  wusb_dev_rm_ncb (void*) ; 

int wusb_usb_ncb(struct notifier_block *nb, unsigned long val,
		 void *priv)
{
	int result = NOTIFY_OK;

	switch (val) {
	case USB_DEVICE_ADD:
		wusb_dev_add_ncb(priv);
		break;
	case USB_DEVICE_REMOVE:
		wusb_dev_rm_ncb(priv);
		break;
	case USB_BUS_ADD:
		/* ignore (for now) */
	case USB_BUS_REMOVE:
		break;
	default:
		WARN_ON(1);
		result = NOTIFY_BAD;
	}
	return result;
}