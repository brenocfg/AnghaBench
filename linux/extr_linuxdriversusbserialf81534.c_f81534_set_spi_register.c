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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct usb_serial {int dummy; } ;

/* Variables and functions */
 int f81534_set_register (struct usb_serial*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int f81534_wait_for_spi_idle (struct usb_serial*) ; 

__attribute__((used)) static int f81534_set_spi_register(struct usb_serial *serial, u16 reg, u8 data)
{
	int status;

	status = f81534_set_register(serial, reg, data);
	if (status)
		return status;

	return f81534_wait_for_spi_idle(serial);
}