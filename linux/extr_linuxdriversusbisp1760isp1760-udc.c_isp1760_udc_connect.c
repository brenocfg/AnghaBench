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
struct isp1760_udc {int /*<<< orphan*/  vbus_timer; int /*<<< orphan*/  gadget; } ;

/* Variables and functions */
 scalar_t__ ISP1760_VBUS_POLL_INTERVAL ; 
 int /*<<< orphan*/  USB_STATE_POWERED ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  usb_gadget_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isp1760_udc_connect(struct isp1760_udc *udc)
{
	usb_gadget_set_state(&udc->gadget, USB_STATE_POWERED);
	mod_timer(&udc->vbus_timer, jiffies + ISP1760_VBUS_POLL_INTERVAL);
}