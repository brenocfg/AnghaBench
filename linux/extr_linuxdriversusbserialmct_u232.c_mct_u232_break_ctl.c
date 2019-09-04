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
struct mct_u232_private {unsigned char last_lcr; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 unsigned char MCT_U232_SET_BREAK ; 
 int /*<<< orphan*/  mct_u232_set_line_ctrl (struct usb_serial_port*,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mct_u232_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void mct_u232_break_ctl(struct tty_struct *tty, int break_state)
{
	struct usb_serial_port *port = tty->driver_data;
	struct mct_u232_private *priv = usb_get_serial_port_data(port);
	unsigned char lcr;
	unsigned long flags;

	spin_lock_irqsave(&priv->lock, flags);
	lcr = priv->last_lcr;

	if (break_state)
		lcr |= MCT_U232_SET_BREAK;
	spin_unlock_irqrestore(&priv->lock, flags);

	mct_u232_set_line_ctrl(port, lcr);
}