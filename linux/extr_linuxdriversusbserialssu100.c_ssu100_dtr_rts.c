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
struct TYPE_2__ {struct usb_device* dev; } ;

/* Variables and functions */
 int TIOCM_DTR ; 
 int TIOCM_RTS ; 
 int /*<<< orphan*/  UART_MCR ; 
 int /*<<< orphan*/  clear_mctrl (struct usb_device*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  set_mctrl (struct usb_device*,int) ; 
 scalar_t__ ssu100_setregister (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ssu100_dtr_rts(struct usb_serial_port *port, int on)
{
	struct usb_device *dev = port->serial->dev;

	/* Disable flow control */
	if (!on) {
		if (ssu100_setregister(dev, 0, UART_MCR, 0) < 0)
			dev_err(&port->dev, "error from flowcontrol urb\n");
	}
	/* drop RTS and DTR */
	if (on)
		set_mctrl(dev, TIOCM_DTR | TIOCM_RTS);
	else
		clear_mctrl(dev, TIOCM_DTR | TIOCM_RTS);
}