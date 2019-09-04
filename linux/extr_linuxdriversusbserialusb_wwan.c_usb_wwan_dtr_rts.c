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
struct usb_wwan_port_private {int rts_state; int dtr_state; } ;
struct usb_wwan_intf_private {int /*<<< orphan*/  use_send_setup; } ;
struct usb_serial_port {int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 struct usb_wwan_intf_private* usb_get_serial_data (int /*<<< orphan*/ ) ; 
 struct usb_wwan_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_wwan_send_setup (struct usb_serial_port*) ; 

void usb_wwan_dtr_rts(struct usb_serial_port *port, int on)
{
	struct usb_wwan_port_private *portdata;
	struct usb_wwan_intf_private *intfdata;

	intfdata = usb_get_serial_data(port->serial);

	if (!intfdata->use_send_setup)
		return;

	portdata = usb_get_serial_port_data(port);
	/* FIXME: locking */
	portdata->rts_state = on;
	portdata->dtr_state = on;

	usb_wwan_send_setup(port);
}