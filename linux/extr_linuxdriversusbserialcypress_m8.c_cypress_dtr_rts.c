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
struct cypress_private {int line_control; int cmd_ctrl; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int CONTROL_DTR ; 
 int CONTROL_RTS ; 
 int /*<<< orphan*/  cypress_write (int /*<<< orphan*/ *,struct usb_serial_port*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct cypress_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void cypress_dtr_rts(struct usb_serial_port *port, int on)
{
	struct cypress_private *priv = usb_get_serial_port_data(port);
	/* drop dtr and rts */
	spin_lock_irq(&priv->lock);
	if (on == 0)
		priv->line_control = 0;
	else 
		priv->line_control = CONTROL_DTR | CONTROL_RTS;
	priv->cmd_ctrl = 1;
	spin_unlock_irq(&priv->lock);
	cypress_write(NULL, port, NULL, 0);
}