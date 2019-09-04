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
struct usb_interface {int dummy; } ;
struct kaweth_device {int /*<<< orphan*/  opened; int /*<<< orphan*/  device_lock; int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 int /*<<< orphan*/  KAWETH_STATUS_SUSPENDING ; 
 int /*<<< orphan*/  kaweth_resubmit_int_urb (struct kaweth_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kaweth_resubmit_rx_urb (struct kaweth_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct kaweth_device* usb_get_intfdata (struct usb_interface*) ; 

__attribute__((used)) static int kaweth_resume(struct usb_interface *intf)
{
	struct kaweth_device *kaweth = usb_get_intfdata(intf);
	unsigned long flags;

	spin_lock_irqsave(&kaweth->device_lock, flags);
	kaweth->status &= ~KAWETH_STATUS_SUSPENDING;
	spin_unlock_irqrestore(&kaweth->device_lock, flags);

	if (!kaweth->opened)
		return 0;
	kaweth_resubmit_rx_urb(kaweth, GFP_NOIO);
	kaweth_resubmit_int_urb(kaweth, GFP_NOIO);

	return 0;
}