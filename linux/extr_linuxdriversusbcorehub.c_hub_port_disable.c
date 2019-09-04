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
struct usb_port {int /*<<< orphan*/  dev; scalar_t__ child; int /*<<< orphan*/  portnum; } ;
struct usb_hub {struct usb_device* hdev; int /*<<< orphan*/  error; struct usb_port** ports; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  USB_PORT_FEAT_ENABLE ; 
 int /*<<< orphan*/  USB_SS_PORT_LS_U3 ; 
 int /*<<< orphan*/  USB_STATE_NOTATTACHED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ hub_is_superspeed (struct usb_device*) ; 
 int hub_set_port_link_state (struct usb_hub*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hub_usb3_port_prepare_disable (struct usb_hub*,struct usb_port*) ; 
 int usb_clear_port_feature (struct usb_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_device_state (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hub_port_disable(struct usb_hub *hub, int port1, int set_state)
{
	struct usb_port *port_dev = hub->ports[port1 - 1];
	struct usb_device *hdev = hub->hdev;
	int ret = 0;

	if (!hub->error) {
		if (hub_is_superspeed(hub->hdev)) {
			hub_usb3_port_prepare_disable(hub, port_dev);
			ret = hub_set_port_link_state(hub, port_dev->portnum,
						      USB_SS_PORT_LS_U3);
		} else {
			ret = usb_clear_port_feature(hdev, port1,
					USB_PORT_FEAT_ENABLE);
		}
	}
	if (port_dev->child && set_state)
		usb_set_device_state(port_dev->child, USB_STATE_NOTATTACHED);
	if (ret && ret != -ENODEV)
		dev_err(&port_dev->dev, "cannot disable (err = %d)\n", ret);
	return ret;
}