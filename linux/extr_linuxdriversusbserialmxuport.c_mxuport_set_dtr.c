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
struct usb_serial_port {int /*<<< orphan*/  port_number; struct usb_serial* serial; } ;
struct usb_serial {int dummy; } ;
struct mxuport_port {int /*<<< orphan*/  mutex; int /*<<< orphan*/  mcr_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQ_VENDOR_SET_DTR ; 
 int /*<<< orphan*/  UART_MCR_DTR ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mxuport_send_ctrl_urb (struct usb_serial*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct mxuport_port* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int mxuport_set_dtr(struct usb_serial_port *port, int on)
{
	struct mxuport_port *mxport = usb_get_serial_port_data(port);
	struct usb_serial *serial = port->serial;
	int err;

	mutex_lock(&mxport->mutex);

	err = mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_DTR,
				    !!on, port->port_number);
	if (!err) {
		if (on)
			mxport->mcr_state |= UART_MCR_DTR;
		else
			mxport->mcr_state &= ~UART_MCR_DTR;
	}

	mutex_unlock(&mxport->mutex);

	return err;
}