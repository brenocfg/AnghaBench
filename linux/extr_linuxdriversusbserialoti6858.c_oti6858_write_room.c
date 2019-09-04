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
struct usb_serial_port {int /*<<< orphan*/  lock; int /*<<< orphan*/  write_fifo; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;

/* Variables and functions */
 int kfifo_avail (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int oti6858_write_room(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	int room = 0;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	room = kfifo_avail(&port->write_fifo);
	spin_unlock_irqrestore(&port->lock, flags);

	return room;
}