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
struct dev_data {scalar_t__ state; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  GADGETFS_DISCONNECT ; 
 int /*<<< orphan*/  INFO (struct dev_data*,char*) ; 
 scalar_t__ STATE_DEV_UNCONNECTED ; 
 int /*<<< orphan*/  ep0_readable (struct dev_data*) ; 
 struct dev_data* get_gadget_data (struct usb_gadget*) ; 
 int /*<<< orphan*/  next_event (struct dev_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
gadgetfs_disconnect (struct usb_gadget *gadget)
{
	struct dev_data		*dev = get_gadget_data (gadget);
	unsigned long		flags;

	spin_lock_irqsave (&dev->lock, flags);
	if (dev->state == STATE_DEV_UNCONNECTED)
		goto exit;
	dev->state = STATE_DEV_UNCONNECTED;

	INFO (dev, "disconnected\n");
	next_event (dev, GADGETFS_DISCONNECT);
	ep0_readable (dev);
exit:
	spin_unlock_irqrestore (&dev->lock, flags);
}