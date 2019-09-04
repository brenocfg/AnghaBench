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
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct iuu_private {int tiostatus; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct iuu_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int iuu_tiocmget(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	struct iuu_private *priv = usb_get_serial_port_data(port);
	unsigned long flags;
	int rc;

	spin_lock_irqsave(&priv->lock, flags);
	rc = priv->tiostatus;
	spin_unlock_irqrestore(&priv->lock, flags);

	return rc;
}