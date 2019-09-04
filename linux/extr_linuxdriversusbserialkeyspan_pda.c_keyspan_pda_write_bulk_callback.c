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
struct usb_serial_port {int /*<<< orphan*/  write_urbs_free; } ;
struct urb {struct usb_serial_port* context; } ;
struct keyspan_pda_private {int /*<<< orphan*/  wakeup_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct keyspan_pda_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static void keyspan_pda_write_bulk_callback(struct urb *urb)
{
	struct usb_serial_port *port = urb->context;
	struct keyspan_pda_private *priv;

	set_bit(0, &port->write_urbs_free);
	priv = usb_get_serial_port_data(port);

	/* queue up a wakeup at scheduler time */
	schedule_work(&priv->wakeup_work);
}