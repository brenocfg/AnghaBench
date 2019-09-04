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
struct catc {int /*<<< orphan*/  netdev; int /*<<< orphan*/  irq_urb; int /*<<< orphan*/  rx_urb; int /*<<< orphan*/  tx_urb; int /*<<< orphan*/  ctrl_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct catc* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void catc_disconnect(struct usb_interface *intf)
{
	struct catc *catc = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);
	if (catc) {
		unregister_netdev(catc->netdev);
		usb_free_urb(catc->ctrl_urb);
		usb_free_urb(catc->tx_urb);
		usb_free_urb(catc->rx_urb);
		usb_free_urb(catc->irq_urb);
		free_netdev(catc->netdev);
	}
}