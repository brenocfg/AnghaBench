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
struct usb_line6 {int dummy; } ;

/* Variables and functions */
 int line6_read_data (struct usb_line6*,int,int /*<<< orphan*/ *,int) ; 

int line6_read_serial_number(struct usb_line6 *line6, u32 *serial_number)
{
	return line6_read_data(line6, 0x80d0, serial_number,
			       sizeof(*serial_number));
}