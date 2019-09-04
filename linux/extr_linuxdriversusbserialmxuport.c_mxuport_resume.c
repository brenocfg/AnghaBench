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
struct usb_serial_port {int /*<<< orphan*/  port; } ;
struct usb_serial {int num_ports; struct usb_serial_port** port; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  tty_port_initialized (int /*<<< orphan*/ *) ; 
 int usb_serial_generic_submit_read_urbs (struct usb_serial_port*,int /*<<< orphan*/ ) ; 
 int usb_serial_generic_write_start (struct usb_serial_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mxuport_resume(struct usb_serial *serial)
{
	struct usb_serial_port *port;
	int c = 0;
	int i;
	int r;

	for (i = 0; i < 2; i++) {
		port = serial->port[i];

		r = usb_serial_generic_submit_read_urbs(port, GFP_NOIO);
		if (r < 0)
			c++;
	}

	for (i = 0; i < serial->num_ports; i++) {
		port = serial->port[i];
		if (!tty_port_initialized(&port->port))
			continue;

		r = usb_serial_generic_write_start(port, GFP_NOIO);
		if (r < 0)
			c++;
	}

	return c ? -EIO : 0;
}