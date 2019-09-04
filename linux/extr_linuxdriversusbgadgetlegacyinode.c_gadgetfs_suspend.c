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
struct usb_gadget {int dummy; } ;
struct dev_data {int state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GADGETFS_SUSPEND ; 
 int /*<<< orphan*/  INFO (struct dev_data*,char*,int) ; 
#define  STATE_DEV_CONNECTED 130 
#define  STATE_DEV_SETUP 129 
#define  STATE_DEV_UNCONNECTED 128 
 int /*<<< orphan*/  ep0_readable (struct dev_data*) ; 
 struct dev_data* get_gadget_data (struct usb_gadget*) ; 
 int /*<<< orphan*/  next_event (struct dev_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
gadgetfs_suspend (struct usb_gadget *gadget)
{
	struct dev_data		*dev = get_gadget_data (gadget);
	unsigned long		flags;

	INFO (dev, "suspended from state %d\n", dev->state);
	spin_lock_irqsave(&dev->lock, flags);
	switch (dev->state) {
	case STATE_DEV_SETUP:		// VERY odd... host died??
	case STATE_DEV_CONNECTED:
	case STATE_DEV_UNCONNECTED:
		next_event (dev, GADGETFS_SUSPEND);
		ep0_readable (dev);
		/* FALLTHROUGH */
	default:
		break;
	}
	spin_unlock_irqrestore(&dev->lock, flags);
}