#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_serial_endpoints {unsigned char num_bulk_in; unsigned char num_bulk_out; int num_interrupt_in; } ;
struct usb_serial {TYPE_4__* interface; TYPE_1__* type; } ;
struct device {int dummy; } ;
struct TYPE_8__ {TYPE_3__* cur_altsetting; struct device dev; } ;
struct TYPE_6__ {int bNumEndpoints; } ;
struct TYPE_7__ {TYPE_2__ desc; } ;
struct TYPE_5__ {unsigned char num_ports; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

__attribute__((used)) static int edge_calc_num_ports(struct usb_serial *serial,
				struct usb_serial_endpoints *epds)
{
	struct device *dev = &serial->interface->dev;
	unsigned char num_ports = serial->type->num_ports;

	/* Make sure we have the required endpoints when in download mode. */
	if (serial->interface->cur_altsetting->desc.bNumEndpoints > 1) {
		if (epds->num_bulk_in < num_ports ||
				epds->num_bulk_out < num_ports ||
				epds->num_interrupt_in < 1) {
			dev_err(dev, "required endpoints missing\n");
			return -ENODEV;
		}
	}

	return num_ports;
}