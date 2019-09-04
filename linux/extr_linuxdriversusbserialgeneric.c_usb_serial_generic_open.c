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
struct usb_serial_port {scalar_t__ bulk_in_size; int /*<<< orphan*/  lock; scalar_t__ throttle_req; scalar_t__ throttled; } ;
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_serial_generic_submit_read_urbs (struct usb_serial_port*,int /*<<< orphan*/ ) ; 

int usb_serial_generic_open(struct tty_struct *tty, struct usb_serial_port *port)
{
	int result = 0;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	port->throttled = 0;
	port->throttle_req = 0;
	spin_unlock_irqrestore(&port->lock, flags);

	if (port->bulk_in_size)
		result = usb_serial_generic_submit_read_urbs(port, GFP_KERNEL);

	return result;
}