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
struct vudc {int /*<<< orphan*/  lock; } ;
struct vep {int /*<<< orphan*/ * desc; } ;
struct TYPE_2__ {scalar_t__ type_control; } ;
struct usb_ep {TYPE_1__ caps; } ;

/* Variables and functions */
 int EINVAL ; 
 struct vudc* ep_to_vudc (struct vep*) ; 
 int /*<<< orphan*/  nuke (struct vudc*,struct vep*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vep* to_vep (struct usb_ep*) ; 

__attribute__((used)) static int vep_disable(struct usb_ep *_ep)
{
	struct vep *ep;
	struct vudc *udc;
	unsigned long flags;

	ep = to_vep(_ep);
	udc = ep_to_vudc(ep);
	if (!_ep || !ep->desc || _ep->caps.type_control)
		return -EINVAL;

	spin_lock_irqsave(&udc->lock, flags);
	ep->desc = NULL;
	nuke(udc, ep);
	spin_unlock_irqrestore(&udc->lock, flags);

	return 0;
}