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
#define  QT2_LINE_STATUS 129 
#define  QT2_MODEM_STATUS 128 
 int /*<<< orphan*/  qt2_update_lsr (struct usb_serial_port*,unsigned char*) ; 
 int /*<<< orphan*/  qt2_update_msr (struct usb_serial_port*,unsigned char*) ; 

__attribute__((used)) static void qt2_process_status(struct usb_serial_port *port, unsigned char *ch)
{
	switch (*ch) {
	case QT2_LINE_STATUS:
		qt2_update_lsr(port, ch + 1);
		break;
	case QT2_MODEM_STATUS:
		qt2_update_msr(port, ch + 1);
		break;
	}
}