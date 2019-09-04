#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct usb_serial_port {TYPE_2__* write_urb; int /*<<< orphan*/  bulk_out_endpointAddress; TYPE_1__* serial; } ;
struct iuu_private {scalar_t__ reset; } ;
struct TYPE_5__ {char* transfer_buffer; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  IUU_DELAY_MS ; 
 char IUU_RST_CLEAR ; 
 int /*<<< orphan*/  IUU_RST_SET ; 
 int /*<<< orphan*/  iuu_rxcmd ; 
 int /*<<< orphan*/  usb_fill_bulk_urb (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct usb_serial_port*) ; 
 struct iuu_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_submit_urb (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iuu_reset(struct usb_serial_port *port, u8 wt)
{
	struct iuu_private *priv = usb_get_serial_port_data(port);
	int result;
	char *buf_ptr = port->write_urb->transfer_buffer;

	/* Prepare the reset sequence */

	*buf_ptr++ = IUU_RST_SET;
	*buf_ptr++ = IUU_DELAY_MS;
	*buf_ptr++ = wt;
	*buf_ptr = IUU_RST_CLEAR;

	/* send the sequence */

	usb_fill_bulk_urb(port->write_urb,
			  port->serial->dev,
			  usb_sndbulkpipe(port->serial->dev,
					  port->bulk_out_endpointAddress),
			  port->write_urb->transfer_buffer, 4, iuu_rxcmd, port);
	result = usb_submit_urb(port->write_urb, GFP_ATOMIC);
	priv->reset = 0;
	return result;
}