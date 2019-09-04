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
typedef  int u32 ;
struct renesas_usb3 {scalar_t__ softconnect; } ;

/* Variables and functions */
 int USB20_CON_B2_CONNECT ; 
 int USB20_CON_B2_PUE ; 
 int /*<<< orphan*/  USB3_USB20_CON ; 
 int /*<<< orphan*/  usb3_clear_bit (struct renesas_usb3*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb3_set_bit (struct renesas_usb3*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usb3_usb2_pullup(struct renesas_usb3 *usb3, int pullup)
{
	u32 bits = USB20_CON_B2_PUE | USB20_CON_B2_CONNECT;

	if (usb3->softconnect && pullup)
		usb3_set_bit(usb3, bits, USB3_USB20_CON);
	else
		usb3_clear_bit(usb3, bits, USB3_USB20_CON);
}