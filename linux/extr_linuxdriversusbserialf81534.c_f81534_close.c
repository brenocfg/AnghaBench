#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_serial_port {int /*<<< orphan*/ * read_urbs; int /*<<< orphan*/  lock; int /*<<< orphan*/  write_fifo; int /*<<< orphan*/ * write_urbs; TYPE_1__* serial; } ;
struct f81534_serial_private {int /*<<< orphan*/  urb_mutex; int /*<<< orphan*/  opened_port; } ;
struct TYPE_2__ {struct usb_serial_port** port; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_reset_out (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct f81534_serial_private* usb_get_serial_data (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void f81534_close(struct usb_serial_port *port)
{
	struct f81534_serial_private *serial_priv =
			usb_get_serial_data(port->serial);
	struct usb_serial_port *port0 = port->serial->port[0];
	unsigned long flags;
	size_t i;

	usb_kill_urb(port->write_urbs[0]);

	spin_lock_irqsave(&port->lock, flags);
	kfifo_reset_out(&port->write_fifo);
	spin_unlock_irqrestore(&port->lock, flags);

	/* Kill Read URBs when final port closed */
	mutex_lock(&serial_priv->urb_mutex);
	serial_priv->opened_port--;

	if (!serial_priv->opened_port) {
		for (i = 0; i < ARRAY_SIZE(port0->read_urbs); ++i)
			usb_kill_urb(port0->read_urbs[i]);
	}

	mutex_unlock(&serial_priv->urb_mutex);
}