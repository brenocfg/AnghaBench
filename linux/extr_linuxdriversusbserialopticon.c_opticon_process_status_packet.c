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
struct opticon_private {int cts; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct opticon_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void opticon_process_status_packet(struct usb_serial_port *port,
					const unsigned char *buf, size_t len)
{
	struct opticon_private *priv = usb_get_serial_port_data(port);
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	if (buf[0] == 0x00)
		priv->cts = false;
	else
		priv->cts = true;
	spin_unlock_irqrestore(&priv->lock, flags);
}