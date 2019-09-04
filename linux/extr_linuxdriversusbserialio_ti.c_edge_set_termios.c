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
struct tty_struct {int dummy; } ;
struct ktermios {int dummy; } ;
struct edgeport_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  change_port_settings (struct tty_struct*,struct edgeport_port*,struct ktermios*) ; 
 struct edgeport_port* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void edge_set_termios(struct tty_struct *tty,
		struct usb_serial_port *port, struct ktermios *old_termios)
{
	struct edgeport_port *edge_port = usb_get_serial_port_data(port);

	if (edge_port == NULL)
		return;
	/* change the port settings to the new ones specified */
	change_port_settings(tty, edge_port, old_termios);
}