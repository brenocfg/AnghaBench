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
struct usb_serial_port {int dummy; } ;
struct urb {int /*<<< orphan*/  status; } ;
struct tty_struct {struct usb_serial_port* driver_data; } ;
struct keyspan_port_private {int out_flip; struct urb** out_urbs; struct keyspan_device_details* device_details; } ;
struct keyspan_device_details {scalar_t__ msg_format; int outdat_endp_flip; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINPROGRESS ; 
 scalar_t__ msg_usa90 ; 
 struct keyspan_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 

__attribute__((used)) static int keyspan_write_room(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	struct keyspan_port_private	*p_priv;
	const struct keyspan_device_details	*d_details;
	int				flip;
	int				data_len;
	struct urb			*this_urb;

	p_priv = usb_get_serial_port_data(port);
	d_details = p_priv->device_details;

	/* FIXME: locking */
	if (d_details->msg_format == msg_usa90)
		data_len = 64;
	else
		data_len = 63;

	flip = p_priv->out_flip;

	/* Check both endpoints to see if any are available. */
	this_urb = p_priv->out_urbs[flip];
	if (this_urb != NULL) {
		if (this_urb->status != -EINPROGRESS)
			return data_len;
		flip = (flip + 1) & d_details->outdat_endp_flip;
		this_urb = p_priv->out_urbs[flip];
		if (this_urb != NULL) {
			if (this_urb->status != -EINPROGRESS)
				return data_len;
		}
	}
	return 0;
}