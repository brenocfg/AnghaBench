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
struct tty_struct {struct usb_serial_port* driver_data; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
#define  TIOCGSERIAL 128 
 int f81232_get_serial_info (struct usb_serial_port*,unsigned long) ; 

__attribute__((used)) static int f81232_ioctl(struct tty_struct *tty,
			unsigned int cmd, unsigned long arg)
{
	struct usb_serial_port *port = tty->driver_data;

	switch (cmd) {
	case TIOCGSERIAL:
		return f81232_get_serial_info(port, arg);
	default:
		break;
	}
	return -ENOIOCTLCMD;
}