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
struct usb_serial_driver {scalar_t__ tx_empty; } ;

/* Variables and functions */
 int /*<<< orphan*/  chars_in_buffer ; 
 int /*<<< orphan*/  close ; 
 int /*<<< orphan*/  open ; 
 int /*<<< orphan*/  prepare_write_buffer ; 
 int /*<<< orphan*/  process_read_urb ; 
 int /*<<< orphan*/  read_bulk_callback ; 
 int /*<<< orphan*/  set_to_generic_if_null (struct usb_serial_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_until_sent ; 
 int /*<<< orphan*/  write ; 
 int /*<<< orphan*/  write_bulk_callback ; 
 int /*<<< orphan*/  write_room ; 

__attribute__((used)) static void usb_serial_operations_init(struct usb_serial_driver *device)
{
	set_to_generic_if_null(device, open);
	set_to_generic_if_null(device, write);
	set_to_generic_if_null(device, close);
	set_to_generic_if_null(device, write_room);
	set_to_generic_if_null(device, chars_in_buffer);
	if (device->tx_empty)
		set_to_generic_if_null(device, wait_until_sent);
	set_to_generic_if_null(device, read_bulk_callback);
	set_to_generic_if_null(device, write_bulk_callback);
	set_to_generic_if_null(device, process_read_urb);
	set_to_generic_if_null(device, prepare_write_buffer);
}