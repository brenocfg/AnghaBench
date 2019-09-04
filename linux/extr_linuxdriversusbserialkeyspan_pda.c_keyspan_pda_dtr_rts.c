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
struct usb_serial_port {struct usb_serial* serial; } ;
struct usb_serial {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  keyspan_pda_set_modem_info (struct usb_serial*,int) ; 

__attribute__((used)) static void keyspan_pda_dtr_rts(struct usb_serial_port *port, int on)
{
	struct usb_serial *serial = port->serial;

	if (on)
		keyspan_pda_set_modem_info(serial, (1 << 7) | (1 << 2));
	else
		keyspan_pda_set_modem_info(serial, 0);
}