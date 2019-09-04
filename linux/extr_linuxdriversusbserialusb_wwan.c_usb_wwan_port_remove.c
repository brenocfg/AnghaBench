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
struct usb_wwan_port_private {struct usb_wwan_port_private** out_buffer; int /*<<< orphan*/ * out_urbs; scalar_t__* in_buffer; int /*<<< orphan*/ * in_urbs; } ;
struct usb_serial_port {int dummy; } ;

/* Variables and functions */
 int N_IN_URB ; 
 int N_OUT_URB ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct usb_wwan_port_private*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct usb_wwan_port_private* usb_get_serial_port_data (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_set_serial_port_data (struct usb_serial_port*,int /*<<< orphan*/ *) ; 

int usb_wwan_port_remove(struct usb_serial_port *port)
{
	int i;
	struct usb_wwan_port_private *portdata;

	portdata = usb_get_serial_port_data(port);
	usb_set_serial_port_data(port, NULL);

	for (i = 0; i < N_IN_URB; i++) {
		usb_free_urb(portdata->in_urbs[i]);
		free_page((unsigned long)portdata->in_buffer[i]);
	}
	for (i = 0; i < N_OUT_URB; i++) {
		usb_free_urb(portdata->out_urbs[i]);
		kfree(portdata->out_buffer[i]);
	}

	kfree(portdata);

	return 0;
}