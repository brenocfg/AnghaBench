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
struct usb_serial_port {int /*<<< orphan*/  serial; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct ark3116_private {int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  lcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  UART_LCR ; 
 int /*<<< orphan*/  UART_LCR_SBC ; 
 int /*<<< orphan*/  ark3116_write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ark3116_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void ark3116_break_ctl(struct tty_struct *tty, int break_state)
{
	struct usb_serial_port *port = tty->driver_data;
	struct ark3116_private *priv = usb_get_serial_port_data(port);

	/* LCR is also used for other things: protect access */
	mutex_lock(&priv->hw_lock);

	if (break_state)
		priv->lcr |= UART_LCR_SBC;
	else
		priv->lcr &= ~UART_LCR_SBC;

	ark3116_write_reg(port->serial, UART_LCR, priv->lcr);

	mutex_unlock(&priv->hw_lock);
}