#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct usb_serial_endpoints {int dummy; } ;
struct usb_serial {TYPE_3__* interface; } ;
struct TYPE_6__ {TYPE_2__* cur_altsetting; } ;
struct TYPE_4__ {int bInterfaceNumber; int bNumEndpoints; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */

__attribute__((used)) static int sierra_calc_num_ports(struct usb_serial *serial,
					struct usb_serial_endpoints *epds)
{
	int num_ports = 0;
	u8 ifnum, numendpoints;

	ifnum = serial->interface->cur_altsetting->desc.bInterfaceNumber;
	numendpoints = serial->interface->cur_altsetting->desc.bNumEndpoints;

	/* Dummy interface present on some SKUs should be ignored */
	if (ifnum == 0x99)
		num_ports = 0;
	else if (numendpoints <= 3)
		num_ports = 1;
	else
		num_ports = (numendpoints-1)/2;
	return num_ports;
}