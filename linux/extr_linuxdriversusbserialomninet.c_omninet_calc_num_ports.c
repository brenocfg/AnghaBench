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
struct usb_serial_endpoints {int num_bulk_out; int /*<<< orphan*/ * bulk_out; } ;
struct usb_serial {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int omninet_calc_num_ports(struct usb_serial *serial,
					struct usb_serial_endpoints *epds)
{
	/* We need only the second bulk-out for our single-port device. */
	epds->bulk_out[0] = epds->bulk_out[1];
	epds->num_bulk_out = 1;

	return 1;
}