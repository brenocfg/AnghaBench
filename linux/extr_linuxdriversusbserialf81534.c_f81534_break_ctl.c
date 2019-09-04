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
struct usb_serial_port {int /*<<< orphan*/  dev; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct f81534_port_private {int /*<<< orphan*/  lcr_mutex; int /*<<< orphan*/  shadow_lcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  F81534_LINE_CONTROL_REG ; 
 int /*<<< orphan*/  UART_LCR_SBC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int f81534_set_port_register (struct usb_serial_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct f81534_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void f81534_break_ctl(struct tty_struct *tty, int break_state)
{
	struct usb_serial_port *port = tty->driver_data;
	struct f81534_port_private *port_priv = usb_get_serial_port_data(port);
	int status;

	mutex_lock(&port_priv->lcr_mutex);

	if (break_state)
		port_priv->shadow_lcr |= UART_LCR_SBC;
	else
		port_priv->shadow_lcr &= ~UART_LCR_SBC;

	status = f81534_set_port_register(port, F81534_LINE_CONTROL_REG,
					port_priv->shadow_lcr);
	if (status)
		dev_err(&port->dev, "set break failed: %d\n", status);

	mutex_unlock(&port_priv->lcr_mutex);
}