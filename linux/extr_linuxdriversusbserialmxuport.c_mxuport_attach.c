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
struct usb_serial_port {int dummy; } ;
struct usb_serial {struct usb_serial_port** port; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  usb_serial_generic_close (struct usb_serial_port*) ; 
 int usb_serial_generic_submit_read_urbs (struct usb_serial_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxuport_attach(struct usb_serial *serial)
{
	struct usb_serial_port *port0 = serial->port[0];
	struct usb_serial_port *port1 = serial->port[1];
	int err;

	/*
	 * All data from the ports is received on the first bulk in
	 * endpoint, with a multiplex header. The second bulk in is
	 * used for events.
	 *
	 * Start to read from the device.
	 */
	err = usb_serial_generic_submit_read_urbs(port0, GFP_KERNEL);
	if (err)
		return err;

	err = usb_serial_generic_submit_read_urbs(port1, GFP_KERNEL);
	if (err) {
		usb_serial_generic_close(port0);
		return err;
	}

	return 0;
}