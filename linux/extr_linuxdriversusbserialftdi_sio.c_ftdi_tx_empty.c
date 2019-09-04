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

/* Variables and functions */
 unsigned char FTDI_RS_TEMT ; 
 int ftdi_get_modem_status (struct usb_serial_port*,unsigned char*) ; 

__attribute__((used)) static bool ftdi_tx_empty(struct usb_serial_port *port)
{
	unsigned char buf[2];
	int ret;

	ret = ftdi_get_modem_status(port, buf);
	if (ret == 2) {
		if (!(buf[1] & FTDI_RS_TEMT))
			return false;
	}

	return true;
}