#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {scalar_t__ console; } ;
struct usb_serial_port {TYPE_1__ port; scalar_t__ sysrq; } ;
struct urb {int actual_length; scalar_t__ transfer_buffer; struct usb_serial_port* context; } ;

/* Variables and functions */
 char TTY_NORMAL ; 
 int /*<<< orphan*/  ssu100_update_lsr (struct usb_serial_port*,char,char*) ; 
 int /*<<< orphan*/  ssu100_update_msr (struct usb_serial_port*,char) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (TYPE_1__*,char,char) ; 
 int /*<<< orphan*/  tty_insert_flip_string_fixed_flag (TYPE_1__*,char*,char,int) ; 
 int /*<<< orphan*/  usb_serial_handle_sysrq_char (struct usb_serial_port*,char) ; 

__attribute__((used)) static void ssu100_process_read_urb(struct urb *urb)
{
	struct usb_serial_port *port = urb->context;
	char *packet = (char *)urb->transfer_buffer;
	char flag = TTY_NORMAL;
	u32 len = urb->actual_length;
	int i;
	char *ch;

	if ((len >= 4) &&
	    (packet[0] == 0x1b) && (packet[1] == 0x1b) &&
	    ((packet[2] == 0x00) || (packet[2] == 0x01))) {
		if (packet[2] == 0x00)
			ssu100_update_lsr(port, packet[3], &flag);
		if (packet[2] == 0x01)
			ssu100_update_msr(port, packet[3]);

		len -= 4;
		ch = packet + 4;
	} else
		ch = packet;

	if (!len)
		return;	/* status only */

	if (port->port.console && port->sysrq) {
		for (i = 0; i < len; i++, ch++) {
			if (!usb_serial_handle_sysrq_char(port, *ch))
				tty_insert_flip_char(&port->port, *ch, flag);
		}
	} else
		tty_insert_flip_string_fixed_flag(&port->port, ch, flag, len);

	tty_flip_buffer_push(&port->port);
}