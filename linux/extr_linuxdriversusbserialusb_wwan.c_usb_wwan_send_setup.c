#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_wwan_port_private {scalar_t__ rts_state; scalar_t__ dtr_state; } ;
struct usb_serial_port {struct usb_serial* serial; } ;
struct usb_serial {TYPE_3__* interface; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_2__* cur_altsetting; } ;
struct TYPE_5__ {int bInterfaceNumber; } ;
struct TYPE_6__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int usb_autopm_get_interface (TYPE_3__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_3__*) ; 
 int usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_wwan_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_wwan_send_setup(struct usb_serial_port *port)
{
	struct usb_serial *serial = port->serial;
	struct usb_wwan_port_private *portdata;
	int val = 0;
	int ifnum;
	int res;

	portdata = usb_get_serial_port_data(port);

	if (portdata->dtr_state)
		val |= 0x01;
	if (portdata->rts_state)
		val |= 0x02;

	ifnum = serial->interface->cur_altsetting->desc.bInterfaceNumber;

	res = usb_autopm_get_interface(serial->interface);
	if (res)
		return res;

	res = usb_control_msg(serial->dev, usb_sndctrlpipe(serial->dev, 0),
				0x22, 0x21, val, ifnum, NULL, 0,
				USB_CTRL_SET_TIMEOUT);

	usb_autopm_put_interface(port->serial->interface);

	return res;
}