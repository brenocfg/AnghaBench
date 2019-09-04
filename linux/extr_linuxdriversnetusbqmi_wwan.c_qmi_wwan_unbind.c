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
struct usbnet {TYPE_2__* udev; int /*<<< orphan*/  data; } ;
struct usb_interface {int dummy; } ;
struct usb_driver {int dummy; } ;
struct qmi_wwan_state {struct usb_interface* control; struct usb_interface* data; TYPE_3__* subdriver; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* disconnect ) (struct usb_interface*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  bcdUSB; } ;
struct TYPE_5__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 struct usb_driver* driver_of (struct usb_interface*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qmi_wwan_change_dtr (struct usbnet*,int) ; 
 int /*<<< orphan*/  qmi_wwan_manage_power (struct usbnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_driver_release_interface (struct usb_driver*,struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void qmi_wwan_unbind(struct usbnet *dev, struct usb_interface *intf)
{
	struct qmi_wwan_state *info = (void *)&dev->data;
	struct usb_driver *driver = driver_of(intf);
	struct usb_interface *other;

	if (info->subdriver && info->subdriver->disconnect)
		info->subdriver->disconnect(info->control);

	/* disable MDM9x30 quirk */
	if (le16_to_cpu(dev->udev->descriptor.bcdUSB) >= 0x0201) {
		qmi_wwan_change_dtr(dev, false);
		qmi_wwan_manage_power(dev, 0);
	}

	/* allow user to unbind using either control or data */
	if (intf == info->control)
		other = info->data;
	else
		other = info->control;

	/* only if not shared */
	if (other && intf != other) {
		usb_set_intfdata(other, NULL);
		usb_driver_release_interface(driver, other);
	}

	info->subdriver = NULL;
	info->data = NULL;
	info->control = NULL;
}