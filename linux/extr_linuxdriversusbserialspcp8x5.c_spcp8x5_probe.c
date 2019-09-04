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
struct usb_serial {int dummy; } ;
struct usb_device_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  usb_set_serial_data (struct usb_serial*,void*) ; 

__attribute__((used)) static int spcp8x5_probe(struct usb_serial *serial,
						const struct usb_device_id *id)
{
	usb_set_serial_data(serial, (void *)id);

	return 0;
}