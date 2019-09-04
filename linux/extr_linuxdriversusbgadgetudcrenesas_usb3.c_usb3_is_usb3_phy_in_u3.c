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
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int USB30_CON_POW_SEL_IN_U3 ; 
 int /*<<< orphan*/  USB3_USB30_CON ; 
 int usb3_read (struct renesas_usb3*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb3_is_usb3_phy_in_u3(struct renesas_usb3 *usb3)
{
	return usb3_read(usb3, USB3_USB30_CON) & USB30_CON_POW_SEL_IN_U3;
}