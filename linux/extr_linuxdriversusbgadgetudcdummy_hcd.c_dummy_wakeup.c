#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_gadget {int dummy; } ;
struct dummy_hcd {int port_status; scalar_t__ rh_state; int resuming; scalar_t__ re_timeout; TYPE_1__* dum; } ;
struct TYPE_4__ {int /*<<< orphan*/  rh_timer; } ;
struct TYPE_3__ {int devstatus; } ;

/* Variables and functions */
 scalar_t__ DUMMY_RH_SUSPENDED ; 
 int EINVAL ; 
 int EIO ; 
 int ENOLINK ; 
 int USB_DEVICE_B_HNP_ENABLE ; 
 int USB_DEVICE_REMOTE_WAKEUP ; 
 int USB_PORT_STAT_CONNECTION ; 
 int USB_PORT_STAT_SUSPEND ; 
 TYPE_2__* dummy_hcd_to_hcd (struct dummy_hcd*) ; 
 struct dummy_hcd* gadget_to_dummy_hcd (struct usb_gadget*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 

__attribute__((used)) static int dummy_wakeup(struct usb_gadget *_gadget)
{
	struct dummy_hcd *dum_hcd;

	dum_hcd = gadget_to_dummy_hcd(_gadget);
	if (!(dum_hcd->dum->devstatus & ((1 << USB_DEVICE_B_HNP_ENABLE)
				| (1 << USB_DEVICE_REMOTE_WAKEUP))))
		return -EINVAL;
	if ((dum_hcd->port_status & USB_PORT_STAT_CONNECTION) == 0)
		return -ENOLINK;
	if ((dum_hcd->port_status & USB_PORT_STAT_SUSPEND) == 0 &&
			 dum_hcd->rh_state != DUMMY_RH_SUSPENDED)
		return -EIO;

	/* FIXME: What if the root hub is suspended but the port isn't? */

	/* hub notices our request, issues downstream resume, etc */
	dum_hcd->resuming = 1;
	dum_hcd->re_timeout = jiffies + msecs_to_jiffies(20);
	mod_timer(&dummy_hcd_to_hcd(dum_hcd)->rh_timer, dum_hcd->re_timeout);
	return 0;
}