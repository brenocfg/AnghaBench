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
struct mct_u232_private {int /*<<< orphan*/  read_urb; } ;

/* Variables and functions */
 struct mct_u232_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_serial_generic_close (struct usb_serial_port*) ; 

__attribute__((used)) static void mct_u232_close(struct usb_serial_port *port)
{
	struct mct_u232_private *priv = usb_get_serial_port_data(port);

	usb_kill_urb(priv->read_urb);
	usb_kill_urb(port->interrupt_in_urb);

	usb_serial_generic_close(port);
}