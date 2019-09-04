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
struct usb_serial_port {int /*<<< orphan*/  interrupt_out_urb; int /*<<< orphan*/  interrupt_in_urb; int /*<<< orphan*/ * write_urbs; int /*<<< orphan*/ * read_urbs; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_unpoison_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb_serial_port_unpoison_urbs(struct usb_serial_port *port)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(port->read_urbs); ++i)
		usb_unpoison_urb(port->read_urbs[i]);
	for (i = 0; i < ARRAY_SIZE(port->write_urbs); ++i)
		usb_unpoison_urb(port->write_urbs[i]);

	usb_unpoison_urb(port->interrupt_in_urb);
	usb_unpoison_urb(port->interrupt_out_urb);
}