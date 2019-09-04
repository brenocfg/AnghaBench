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
struct usb_serial_port {int /*<<< orphan*/  dev; TYPE_1__* serial; int /*<<< orphan*/  interrupt_in_urb; int /*<<< orphan*/  port; } ;
struct usb_serial {int /*<<< orphan*/  dev; struct usb_serial_port** port; } ;
struct ch341_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  ch341_configure (int /*<<< orphan*/ ,struct ch341_private*) ; 
 int ch341_get_status (int /*<<< orphan*/ ,struct ch341_private*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ tty_port_initialized (int /*<<< orphan*/ *) ; 
 struct ch341_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int usb_serial_generic_resume (struct usb_serial*) ; 
 int usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ch341_reset_resume(struct usb_serial *serial)
{
	struct usb_serial_port *port = serial->port[0];
	struct ch341_private *priv = usb_get_serial_port_data(port);
	int ret;

	/* reconfigure ch341 serial port after bus-reset */
	ch341_configure(serial->dev, priv);

	if (tty_port_initialized(&port->port)) {
		ret = usb_submit_urb(port->interrupt_in_urb, GFP_NOIO);
		if (ret) {
			dev_err(&port->dev, "failed to submit interrupt urb: %d\n",
				ret);
			return ret;
		}

		ret = ch341_get_status(port->serial->dev, priv);
		if (ret < 0) {
			dev_err(&port->dev, "failed to read modem status: %d\n",
				ret);
		}
	}

	return usb_serial_generic_resume(serial);
}