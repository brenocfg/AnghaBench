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
struct usb_serial_port {int throttled; int throttle_req; int /*<<< orphan*/  lock; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_serial_generic_submit_read_urbs (struct usb_serial_port*,int /*<<< orphan*/ ) ; 

void usb_serial_generic_unthrottle(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	int was_throttled;

	spin_lock_irq(&port->lock);
	was_throttled = port->throttled;
	port->throttled = port->throttle_req = 0;
	spin_unlock_irq(&port->lock);

	if (was_throttled)
		usb_serial_generic_submit_read_urbs(port, GFP_KERNEL);
}