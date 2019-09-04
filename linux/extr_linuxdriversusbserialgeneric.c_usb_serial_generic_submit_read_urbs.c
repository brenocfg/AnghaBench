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
struct usb_serial_port {int /*<<< orphan*/ * read_urbs; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 
 int usb_serial_generic_submit_read_urb (struct usb_serial_port*,int,int /*<<< orphan*/ ) ; 

int usb_serial_generic_submit_read_urbs(struct usb_serial_port *port,
					gfp_t mem_flags)
{
	int res;
	int i;

	for (i = 0; i < ARRAY_SIZE(port->read_urbs); ++i) {
		res = usb_serial_generic_submit_read_urb(port, i, mem_flags);
		if (res)
			goto err;
	}

	return 0;
err:
	for (; i >= 0; --i)
		usb_kill_urb(port->read_urbs[i]);

	return res;
}