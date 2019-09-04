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
typedef  scalar_t__ u16 ;
struct usb_serial {int dummy; } ;

/* Variables and functions */
 int F81534_UART_OFFSET ; 
 int f81534_set_register (struct usb_serial*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int f81534_set_phy_port_register(struct usb_serial *serial, int phy,
					u16 reg, u8 data)
{
	return f81534_set_register(serial, reg + F81534_UART_OFFSET * phy,
					data);
}