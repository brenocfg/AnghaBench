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
struct opticon_private {int rts; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTROL_RTS ; 
 unsigned int TIOCM_RTS ; 
 int send_control_msg (struct usb_serial_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct opticon_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int usb_translate_errors (int) ; 

__attribute__((used)) static int opticon_tiocmset(struct tty_struct *tty,
			   unsigned int set, unsigned int clear)
{
	struct usb_serial_port *port = tty->driver_data;
	struct opticon_private *priv = usb_get_serial_port_data(port);
	unsigned long flags;
	bool rts;
	bool changed = false;
	int ret;

	/* We only support RTS so we only handle that */
	spin_lock_irqsave(&priv->lock, flags);

	rts = priv->rts;
	if (set & TIOCM_RTS)
		priv->rts = true;
	if (clear & TIOCM_RTS)
		priv->rts = false;
	changed = rts ^ priv->rts;
	spin_unlock_irqrestore(&priv->lock, flags);

	if (!changed)
		return 0;

	ret = send_control_msg(port, CONTROL_RTS, !rts);
	if (ret)
		return usb_translate_errors(ret);

	return 0;
}