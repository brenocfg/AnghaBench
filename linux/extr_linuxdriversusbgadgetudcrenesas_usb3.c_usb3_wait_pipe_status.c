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
struct renesas_usb3_ep {scalar_t__ num; } ;
struct renesas_usb3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB3_P0_STA ; 
 int /*<<< orphan*/  USB3_PN_STA ; 
 struct renesas_usb3* usb3_ep_to_usb3 (struct renesas_usb3_ep*) ; 
 int usb3_wait (struct renesas_usb3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb3_wait_pipe_status(struct renesas_usb3_ep *usb3_ep, u32 mask)
{
	struct renesas_usb3 *usb3 = usb3_ep_to_usb3(usb3_ep);
	u32 sta_reg = usb3_ep->num ? USB3_PN_STA : USB3_P0_STA;

	return usb3_wait(usb3, sta_reg, mask, mask);
}