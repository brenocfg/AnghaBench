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
struct usb_serial {TYPE_3__* interface; } ;
struct usb_device_id {int dummy; } ;
struct TYPE_6__ {TYPE_2__* cur_altsetting; } ;
struct TYPE_4__ {int bInterfaceNumber; } ;
struct TYPE_5__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static int xsens_mt_probe(struct usb_serial *serial,
					const struct usb_device_id *id)
{
	if (serial->interface->cur_altsetting->desc.bInterfaceNumber == 1)
		return 0;

	return -ENODEV;
}