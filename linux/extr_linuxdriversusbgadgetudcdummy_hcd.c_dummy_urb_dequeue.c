#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct usb_hcd {int dummy; } ;
struct urb {int dummy; } ;
struct dummy_hcd {scalar_t__ rh_state; TYPE_1__* dum; int /*<<< orphan*/  timer; int /*<<< orphan*/  urbp_list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ DUMMY_RH_RUNNING ; 
 struct dummy_hcd* hcd_to_dummy_hcd (struct usb_hcd*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_hcd_check_unlink_urb (struct usb_hcd*,struct urb*,int) ; 

__attribute__((used)) static int dummy_urb_dequeue(struct usb_hcd *hcd, struct urb *urb, int status)
{
	struct dummy_hcd *dum_hcd;
	unsigned long	flags;
	int		rc;

	/* giveback happens automatically in timer callback,
	 * so make sure the callback happens */
	dum_hcd = hcd_to_dummy_hcd(hcd);
	spin_lock_irqsave(&dum_hcd->dum->lock, flags);

	rc = usb_hcd_check_unlink_urb(hcd, urb, status);
	if (!rc && dum_hcd->rh_state != DUMMY_RH_RUNNING &&
			!list_empty(&dum_hcd->urbp_list))
		mod_timer(&dum_hcd->timer, jiffies);

	spin_unlock_irqrestore(&dum_hcd->dum->lock, flags);
	return rc;
}