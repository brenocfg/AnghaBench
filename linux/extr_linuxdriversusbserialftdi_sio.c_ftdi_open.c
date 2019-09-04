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
struct usb_serial_port {TYPE_1__* serial; } ;
struct usb_device {int dummy; } ;
struct tty_struct {int dummy; } ;
struct ftdi_private {int /*<<< orphan*/  interface; } ;
struct TYPE_2__ {struct usb_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTDI_SIO_RESET_REQUEST ; 
 int /*<<< orphan*/  FTDI_SIO_RESET_REQUEST_TYPE ; 
 int /*<<< orphan*/  FTDI_SIO_RESET_SIO ; 
 int /*<<< orphan*/  WDR_TIMEOUT ; 
 int /*<<< orphan*/  ftdi_set_termios (struct tty_struct*,struct usb_serial_port*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ftdi_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int usb_serial_generic_open (struct tty_struct*,struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ftdi_open(struct tty_struct *tty, struct usb_serial_port *port)
{
	struct usb_device *dev = port->serial->dev;
	struct ftdi_private *priv = usb_get_serial_port_data(port);

	/* No error checking for this (will get errors later anyway) */
	/* See ftdi_sio.h for description of what is reset */
	usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
			FTDI_SIO_RESET_REQUEST, FTDI_SIO_RESET_REQUEST_TYPE,
			FTDI_SIO_RESET_SIO,
			priv->interface, NULL, 0, WDR_TIMEOUT);

	/* Termios defaults are set by usb_serial_init. We don't change
	   port->tty->termios - this would lose speed settings, etc.
	   This is same behaviour as serial.c/rs_open() - Kuba */

	/* ftdi_set_termios  will send usb control messages */
	if (tty)
		ftdi_set_termios(tty, port, NULL);

	return usb_serial_generic_open(tty, port);
}