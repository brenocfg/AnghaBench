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
struct usb_serial_endpoints {int num_bulk_in; int num_bulk_out; int /*<<< orphan*/ * bulk_out; int /*<<< orphan*/ * bulk_in; } ;
struct usb_serial {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 

__attribute__((used)) static int ipaq_calc_num_ports(struct usb_serial *serial,
					struct usb_serial_endpoints *epds)
{
	/*
	 * Some of the devices in ipaq_id_table[] are composite, and we
	 * shouldn't bind to all the interfaces. This test will rule out
	 * some obviously invalid possibilities.
	 */
	if (epds->num_bulk_in == 0 || epds->num_bulk_out == 0)
		return -ENODEV;

	/*
	 * A few devices have four endpoints, seemingly Yakuma devices, and
	 * we need the second pair.
	 */
	if (epds->num_bulk_in > 1 && epds->num_bulk_out > 1) {
		epds->bulk_in[0] = epds->bulk_in[1];
		epds->bulk_out[0] = epds->bulk_out[1];
	}

	/*
	 * Other devices have 3 endpoints, but we only use the first bulk in
	 * and out endpoints.
	 */
	epds->num_bulk_in = 1;
	epds->num_bulk_out = 1;

	return 1;
}