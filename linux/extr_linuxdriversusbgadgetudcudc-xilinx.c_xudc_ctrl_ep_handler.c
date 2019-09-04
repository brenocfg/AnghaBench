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
struct xusb_udc {int dummy; } ;

/* Variables and functions */
 int XUSB_STATUS_FIFO_BUFF_FREE_MASK ; 
 int XUSB_STATUS_FIFO_BUFF_RDY_MASK ; 
 int XUSB_STATUS_SETUP_PACKET_MASK ; 
 int /*<<< orphan*/  xudc_ep0_in (struct xusb_udc*) ; 
 int /*<<< orphan*/  xudc_ep0_out (struct xusb_udc*) ; 
 int /*<<< orphan*/  xudc_handle_setup (struct xusb_udc*) ; 

__attribute__((used)) static void xudc_ctrl_ep_handler(struct xusb_udc *udc, u32 intrstatus)
{

	if (intrstatus & XUSB_STATUS_SETUP_PACKET_MASK) {
		xudc_handle_setup(udc);
	} else {
		if (intrstatus & XUSB_STATUS_FIFO_BUFF_RDY_MASK)
			xudc_ep0_out(udc);
		else if (intrstatus & XUSB_STATUS_FIFO_BUFF_FREE_MASK)
			xudc_ep0_in(udc);
	}
}