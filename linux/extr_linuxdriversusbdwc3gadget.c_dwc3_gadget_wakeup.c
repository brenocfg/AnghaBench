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
struct dwc3 {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __dwc3_gadget_wakeup (struct dwc3*) ; 
 struct dwc3* gadget_to_dwc (struct usb_gadget*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int dwc3_gadget_wakeup(struct usb_gadget *g)
{
	struct dwc3		*dwc = gadget_to_dwc(g);
	unsigned long		flags;
	int			ret;

	spin_lock_irqsave(&dwc->lock, flags);
	ret = __dwc3_gadget_wakeup(dwc);
	spin_unlock_irqrestore(&dwc->lock, flags);

	return ret;
}