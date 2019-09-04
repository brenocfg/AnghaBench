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
struct usb_serial_port {int /*<<< orphan*/  interrupt_in_urb; } ;
struct sierra_port_private {int num_in_urbs; int /*<<< orphan*/ * in_urbs; } ;

/* Variables and functions */
 struct sierra_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sierra_stop_rx_urbs(struct usb_serial_port *port)
{
	int i;
	struct sierra_port_private *portdata = usb_get_serial_port_data(port);

	for (i = 0; i < portdata->num_in_urbs; i++)
		usb_kill_urb(portdata->in_urbs[i]);

	usb_kill_urb(port->interrupt_in_urb);
}