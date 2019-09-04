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
struct usb_serial_port {int /*<<< orphan*/  read_urb; int /*<<< orphan*/  write_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cyberjack_close(struct usb_serial_port *port)
{
	usb_kill_urb(port->write_urb);
	usb_kill_urb(port->read_urb);
}