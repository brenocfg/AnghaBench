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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct ipheth_device {int /*<<< orphan*/  net; int /*<<< orphan*/  ctrl_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipheth_free_urbs (struct ipheth_device*) ; 
 int /*<<< orphan*/  ipheth_kill_urbs (struct ipheth_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 struct ipheth_device* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipheth_disconnect(struct usb_interface *intf)
{
	struct ipheth_device *dev;

	dev = usb_get_intfdata(intf);
	if (dev != NULL) {
		unregister_netdev(dev->net);
		ipheth_kill_urbs(dev);
		ipheth_free_urbs(dev);
		kfree(dev->ctrl_buf);
		free_netdev(dev->net);
	}
	usb_set_intfdata(intf, NULL);
	dev_info(&intf->dev, "Apple iPhone USB Ethernet now disconnected\n");
}