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
typedef  int /*<<< orphan*/  u32 ;
struct usb_serial_port {int dummy; } ;

/* Variables and functions */
 int cp210x_get_tx_queue_byte_count (struct usb_serial_port*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool cp210x_tx_empty(struct usb_serial_port *port)
{
	int err;
	u32 count;

	err = cp210x_get_tx_queue_byte_count(port, &count);
	if (err)
		return true;

	return !count;
}