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
struct usb_serial_port {int /*<<< orphan*/  dev; TYPE_1__* serial; } ;
struct usb_device {int dummy; } ;
struct qt2_port_private {int /*<<< orphan*/  device_port; } ;
struct TYPE_2__ {struct usb_device* dev; } ;

/* Variables and functions */
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  UART_MCR ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ qt2_setregister (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_mctrl (struct qt2_port_private*,int,int) ; 
 struct qt2_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void qt2_dtr_rts(struct usb_serial_port *port, int on)
{
	struct usb_device *dev = port->serial->dev;
	struct qt2_port_private *port_priv = usb_get_serial_port_data(port);

	/* Disable flow control */
	if (!on) {
		if (qt2_setregister(dev, port_priv->device_port,
					   UART_MCR, 0) < 0)
			dev_warn(&port->dev, "error from flowcontrol urb\n");
	}
	/* drop RTS and DTR */
	if (on)
		update_mctrl(port_priv, TIOCM_DTR | TIOCM_RTS, 0);
	else
		update_mctrl(port_priv, 0, TIOCM_DTR | TIOCM_RTS);
}