#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_serial_endpoints {scalar_t__ num_interrupt_out; } ;
struct usb_serial {TYPE_1__* interface; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ metrousb_is_unidirectional_mode (struct usb_serial*) ; 

__attribute__((used)) static int metrousb_calc_num_ports(struct usb_serial *serial,
				   struct usb_serial_endpoints *epds)
{
	if (metrousb_is_unidirectional_mode(serial)) {
		if (epds->num_interrupt_out == 0) {
			dev_err(&serial->interface->dev, "interrupt-out endpoint missing\n");
			return -ENODEV;
		}
	}

	return 1;
}