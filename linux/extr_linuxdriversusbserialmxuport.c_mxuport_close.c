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

/* Variables and functions */
 int /*<<< orphan*/  RQ_VENDOR_SET_OPEN ; 
 int /*<<< orphan*/  RQ_VENDOR_SET_RX_HOST_EN ; 
 int /*<<< orphan*/  mxuport_send_ctrl_urb (struct usb_serial*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mxuport_close(struct usb_serial_port *port)
{
	struct usb_serial *serial = port->serial;

	mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_OPEN, 0,
			      port->port_number);

	mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_RX_HOST_EN, 0,
			      port->port_number);
}