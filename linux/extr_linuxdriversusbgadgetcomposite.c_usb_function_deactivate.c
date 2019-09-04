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
struct usb_function {TYPE_1__* config; } ;
struct usb_composite_dev {scalar_t__ deactivations; int /*<<< orphan*/  lock; int /*<<< orphan*/  gadget; } ;
struct TYPE_2__ {struct usb_composite_dev* cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int usb_gadget_deactivate (int /*<<< orphan*/ ) ; 

int usb_function_deactivate(struct usb_function *function)
{
	struct usb_composite_dev	*cdev = function->config->cdev;
	unsigned long			flags;
	int				status = 0;

	spin_lock_irqsave(&cdev->lock, flags);

	if (cdev->deactivations == 0)
		status = usb_gadget_deactivate(cdev->gadget);
	if (status == 0)
		cdev->deactivations++;

	spin_unlock_irqrestore(&cdev->lock, flags);
	return status;
}