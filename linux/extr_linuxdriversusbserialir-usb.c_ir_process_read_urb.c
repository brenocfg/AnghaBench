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
struct usb_serial_port {int /*<<< orphan*/  port; } ;
struct urb {unsigned char* transfer_buffer; int actual_length; struct usb_serial_port* context; } ;

/* Variables and functions */
 unsigned char ir_baud ; 
 int /*<<< orphan*/  tty_flip_buffer_push (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_insert_flip_string (int /*<<< orphan*/ *,unsigned char*,int) ; 

__attribute__((used)) static void ir_process_read_urb(struct urb *urb)
{
	struct usb_serial_port *port = urb->context;
	unsigned char *data = urb->transfer_buffer;

	if (!urb->actual_length)
		return;
	/*
	 * The first byte of the packet we get from the device
	 * contains a busy indicator and baud rate change.
	 * See section 5.4.1.2 of the USB IrDA spec.
	 */
	if (*data & 0x0f)
		ir_baud = *data & 0x0f;

	if (urb->actual_length == 1)
		return;

	tty_insert_flip_string(&port->port, data + 1, urb->actual_length - 1);
	tty_flip_buffer_push(&port->port);
}