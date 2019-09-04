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
struct usb_interface {int dummy; } ;
struct usb_device {int dummy; } ;
struct lvs_rh {int portnum; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  USB_PORT_FEAT_LINK_STATE ; 
 int USB_SS_PORT_LS_COMP_MOD ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int lvs_rh_set_port_feature (struct usb_device*,int,int /*<<< orphan*/ ) ; 
 struct usb_interface* to_usb_interface (struct device*) ; 
 struct lvs_rh* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static ssize_t enable_compliance_store(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct usb_device *hdev = interface_to_usbdev(intf);
	struct lvs_rh *lvs = usb_get_intfdata(intf);
	int ret;

	ret = lvs_rh_set_port_feature(hdev,
			lvs->portnum | USB_SS_PORT_LS_COMP_MOD << 3,
			USB_PORT_FEAT_LINK_STATE);
	if (ret < 0) {
		dev_err(dev, "can't enable compliance mode %d\n", ret);
		return ret;
	}

	return count;
}