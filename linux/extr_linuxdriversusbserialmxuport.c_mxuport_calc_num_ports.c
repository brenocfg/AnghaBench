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
struct usb_serial_endpoints {int num_bulk_out; int /*<<< orphan*/ * bulk_out; } ;
struct usb_serial {TYPE_1__* interface; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 unsigned long MX_UPORT_16_PORT ; 
 unsigned long MX_UPORT_2_PORT ; 
 unsigned long MX_UPORT_4_PORT ; 
 unsigned long MX_UPORT_8_PORT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ usb_get_serial_data (struct usb_serial*) ; 

__attribute__((used)) static int mxuport_calc_num_ports(struct usb_serial *serial,
					struct usb_serial_endpoints *epds)
{
	unsigned long features = (unsigned long)usb_get_serial_data(serial);
	int num_ports;
	int i;

	if (features & MX_UPORT_2_PORT) {
		num_ports = 2;
	} else if (features & MX_UPORT_4_PORT) {
		num_ports = 4;
	} else if (features & MX_UPORT_8_PORT) {
		num_ports = 8;
	} else if (features & MX_UPORT_16_PORT) {
		num_ports = 16;
	} else {
		dev_warn(&serial->interface->dev,
				"unknown device, assuming two ports\n");
		num_ports = 2;
	}

	/*
	 * Setup bulk-out endpoint multiplexing. All ports share the same
	 * bulk-out endpoint.
	 */
	BUILD_BUG_ON(ARRAY_SIZE(epds->bulk_out) < 16);

	for (i = 1; i < num_ports; ++i)
		epds->bulk_out[i] = epds->bulk_out[0];

	epds->num_bulk_out = num_ports;

	return num_ports;
}