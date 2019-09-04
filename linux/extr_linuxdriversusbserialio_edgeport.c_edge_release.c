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
struct usb_serial {int dummy; } ;
struct edgeport_serial {struct edgeport_serial* bulk_in_buffer; int /*<<< orphan*/  read_urb; struct edgeport_serial* interrupt_in_buffer; int /*<<< orphan*/  interrupt_read_urb; scalar_t__ is_epic; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct edgeport_serial*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 struct edgeport_serial* usb_get_serial_data (struct usb_serial*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void edge_release(struct usb_serial *serial)
{
	struct edgeport_serial *edge_serial = usb_get_serial_data(serial);

	if (edge_serial->is_epic) {
		usb_kill_urb(edge_serial->interrupt_read_urb);
		usb_free_urb(edge_serial->interrupt_read_urb);
		kfree(edge_serial->interrupt_in_buffer);

		usb_kill_urb(edge_serial->read_urb);
		usb_free_urb(edge_serial->read_urb);
		kfree(edge_serial->bulk_in_buffer);
	}

	kfree(edge_serial);
}