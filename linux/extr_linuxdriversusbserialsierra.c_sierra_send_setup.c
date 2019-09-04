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
struct usb_serial_port {int bulk_out_endpointAddress; scalar_t__ interrupt_in_urb; struct usb_serial* serial; } ;
struct usb_serial {int num_ports; int /*<<< orphan*/  interface; int /*<<< orphan*/  dev; } ;
struct sierra_port_private {scalar_t__ rts_state; scalar_t__ dtr_state; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int sierra_interface_num (struct usb_serial*) ; 
 int usb_autopm_get_interface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (int /*<<< orphan*/ ) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sierra_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sierra_send_setup(struct usb_serial_port *port)
{
	struct usb_serial *serial = port->serial;
	struct sierra_port_private *portdata;
	__u16 interface = 0;
	int val = 0;
	int do_send = 0;
	int retval;

	portdata = usb_get_serial_port_data(port);

	if (portdata->dtr_state)
		val |= 0x01;
	if (portdata->rts_state)
		val |= 0x02;

	/* If composite device then properly report interface */
	if (serial->num_ports == 1) {
		interface = sierra_interface_num(serial);
		/* Control message is sent only to interfaces with
		 * interrupt_in endpoints
		 */
		if (port->interrupt_in_urb) {
			/* send control message */
			do_send = 1;
		}
	}

	/* Otherwise the need to do non-composite mapping */
	else {
		if (port->bulk_out_endpointAddress == 2)
			interface = 0;
		else if (port->bulk_out_endpointAddress == 4)
			interface = 1;
		else if (port->bulk_out_endpointAddress == 5)
			interface = 2;

		do_send = 1;
	}
	if (!do_send)
		return 0;

	retval = usb_autopm_get_interface(serial->interface);
	if (retval < 0)
		return retval;

	retval = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
		0x22, 0x21, val, interface, NULL, 0, USB_CTRL_SET_TIMEOUT);
	usb_autopm_put_interface(serial->interface);

	return retval;
}