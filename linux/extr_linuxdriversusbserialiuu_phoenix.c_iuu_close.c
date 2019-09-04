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
struct usb_serial_port {int /*<<< orphan*/  read_urb; int /*<<< orphan*/  write_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  iuu_led (struct usb_serial_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  iuu_uart_off (struct usb_serial_port*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iuu_close(struct usb_serial_port *port)
{
	/* iuu_led (port,255,0,0,0); */

	iuu_uart_off(port);

	usb_kill_urb(port->write_urb);
	usb_kill_urb(port->read_urb);

	iuu_led(port, 0, 0, 0xF000, 0xFF);
}